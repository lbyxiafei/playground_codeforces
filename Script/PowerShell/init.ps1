# System::Path: $Get-EnvPath Machine
# User::Path: $Get-EnvPath User
function Get-EnvPath {
    param(
        [Parameter(Mandatory=$true)]
        [ValidateSet('Machine', 'User')]
        [string] $Container
    )

    $containerMapping = @{
        Machine = [EnvironmentVariableTarget]::Machine
        User = [EnvironmentVariableTarget]::User
    }
    $containerType = $containerMapping[$Container]

    [Environment]::GetEnvironmentVariable('Path', $containerType) -split ';' |
        where { $_ }
}

function Remove-EnvPath {
    param(
        [Parameter(Mandatory=$true)]
        [string] $Path,

        [ValidateSet('Machine', 'User', 'Session')]
        [string] $Container = 'Session'
    )

    if ($Container -ne 'Session') {
        $containerMapping = @{
            Machine = [EnvironmentVariableTarget]::Machine
            User = [EnvironmentVariableTarget]::User
        }
        $containerType = $containerMapping[$Container]

        $persistedPaths = [Environment]::GetEnvironmentVariable('Path', $containerType) -split ';'
        if ($persistedPaths -contains $Path) {
            $persistedPaths = $persistedPaths | where { $_ -and $_ -ne $Path }
            [Environment]::SetEnvironmentVariable('Path', $persistedPaths -join ';', $containerType)
        }
    }

    $envPaths = $env:Path -split ';'
    if ($envPaths -contains $Path) {
        $envPaths = $envPaths | where { $_ -and $_ -ne $Path }
        $env:Path = $envPaths -join ';'
    }
}

# Add if not existing
# $Add-EnvPath Machine C:\test
function Add-EnvPath {
    param(
        [Parameter(Mandatory=$true)]
        [string] $Path,

        [ValidateSet('Machine', 'User', 'Session')]
        [string] $Container = 'Session'
    )

    if ($Container -ne 'Session') {
        $containerMapping = @{
            Machine = [EnvironmentVariableTarget]::Machine
            User = [EnvironmentVariableTarget]::User
        }
        $containerType = $containerMapping[$Container]

        $persistedPaths = [Environment]::GetEnvironmentVariable('Path', $containerType) -split ';'
        if ($persistedPaths -notcontains $Path) {
            $persistedPaths = $persistedPaths + $Path | where { $_ }
            [Environment]::SetEnvironmentVariable('Path', $persistedPaths -join ';', $containerType)
        }
    }

    $envPaths = $env:Path -split ';'
    if ($envPaths -notcontains $Path) {
        $envPaths = $envPaths + $Path | where { $_ }
        $env:Path = $envPaths -join ';'
    }
}

function Init-Local-Script-To-EnvPath{
    $pstage=$env:userprofile+"\Repos\Templates\Script\PowerShell"
    $plocal=$env:userprofile+"\Scripts"
    $ts=Get-Date -Format o | ForEach-Object { $_ -replace ":", "." }
    $pdump=$env:userprofile+"\Downloads\Dump\Script\"+$ts

    # Create local script folder if not exist
    New-Item -ItemType Directory -Force -Path $plocal
    # Create dump folder if not exisit
    New-Item -ItemType Directory -Force -Path $pdump
    # Move current local script to dump
    & mv $plocal $pdump

    # Create local script folder if not exist
    New-Item -ItemType Directory -Force -Path $plocal
    # Copy scripts from pstage(template repo/script folder)
    echo $pstage
    cp $pstage/* $plocal

    # Add local script to env::path
    & Add-Local-Script-To-EnvPath

    # Close and restart
    & powershell

    & Write-Host "Init local script folder...done"
}

function Add-Local-Script-To-EnvPath{
    & Write-Host "Add local script to env::path..."
    $plocal=$env:userprofile+"\Scripts"
    & Add-EnvPath $plocal User
    & Write-Host "Add local script to env::path...done"
}

function Run{
    param(
        [Parameter(Mandatory=$true)]
        [ValidateSet('1', '2', '3', '0')]
        [string] $Choice
    )
    if($Choice -eq '1'){
        &Init-Local-Script-To-EnvPath
    }
    else{
        & Write-Host "Choice no-op yet."
    }
}



& Write-Host "Select from:"
& Write-Host "  1. Init local scripts folder."
& Write-Host "  2. ???"
& Write-Host "  0. ???"
& Run
