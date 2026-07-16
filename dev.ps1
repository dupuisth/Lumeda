[CmdletBinding()]
param(
    [ValidateSet("setup", "generate", "build", "rebuild", "run", "test", "clean")]
    [string] $Action = "build",

    [ValidateSet("debug", "release", "profiling")]
    [string] $Configuration = "debug"
)

$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

$Root = $PSScriptRoot
$Premake = Join-Path $Root "vendor\premake\premake5.exe"
$Solution = Join-Path $Root "Lumeda.sln"
$ConfigurationName = (Get-Culture).TextInfo.ToTitleCase($Configuration)
$OutputDirectory = Join-Path $Root "bin\$ConfigurationName-windows-x86_64"

function Invoke-Checked {
    param(
        [Parameter(Mandatory = $true)]
        [string] $FilePath,

        [string[]] $Arguments = @()
    )

    Write-Host "> $FilePath $($Arguments -join ' ')" -ForegroundColor DarkGray
    & $FilePath @Arguments
    if ($LASTEXITCODE -ne 0) {
        throw "Command failed with exit code $LASTEXITCODE."
    }
}

function Get-MSBuild {
    $vswhere = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"
    if (-not (Test-Path $vswhere)) {
        throw "Visual Studio Installer was not found. Install Visual Studio 2022 with the 'Desktop development with C++' workload."
    }

    $installationPath = & $vswhere -latest -products * -requires Microsoft.Component.MSBuild -property installationPath
    if (-not $installationPath) {
        throw "MSBuild was not found. Install the Visual Studio 2022 'Desktop development with C++' workload."
    }

    $msbuild = Join-Path $installationPath "MSBuild\Current\Bin\MSBuild.exe"
    if (-not (Test-Path $msbuild)) {
        throw "MSBuild was not found in $installationPath."
    }

    return $msbuild
}

function Invoke-Generate {
    if (-not (Test-Path $Premake)) {
        throw "Premake was not found. Run this command first: git submodule update --init --recursive"
    }

    Push-Location $Root
    try {
        Invoke-Checked $Premake @("vs2022")
    }
    finally {
        Pop-Location
    }
}

function Invoke-Build {
    param([ValidateSet("Build", "Rebuild", "Clean")] [string] $Target = "Build")

    Invoke-Generate

    $msbuild = Get-MSBuild
    Invoke-Checked $msbuild @(
        $Solution,
        "/m",
        "/t:$Target",
        "/p:Configuration=$ConfigurationName",
        "/p:Platform=x64",
        "/verbosity:minimal",
        "/nologo"
    )
}

switch ($Action) {
    "setup" {
        Invoke-Checked "git" @("-C", $Root, "submodule", "update", "--init", "--recursive")
        Invoke-Generate
    }
    "generate" { Invoke-Generate }
    "build" { Invoke-Build }
    "rebuild" { Invoke-Generate; Invoke-Build "Rebuild" }
    "clean" { Invoke-Build "Clean" }
    "run" {
        Invoke-Build
        $program = Join-Path $OutputDirectory "Sandbox\Sandbox.exe"
        if (-not (Test-Path $program)) {
            throw "Executable not found: $program"
        }

        Push-Location (Join-Path $Root "Sandbox")
        try {
            Invoke-Checked $program
        }
        finally {
            Pop-Location
        }
    }
    "test" {
        Invoke-Build
        $program = Join-Path $OutputDirectory "LumedaTest\LumedaTest.exe"
        if (-not (Test-Path $program)) {
            throw "Tests are currently disabled in premake5.lua (the LumedaTest project uses kind 'None')."
        }
        Invoke-Checked $program
    }
}
