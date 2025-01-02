# Export file for FlappyBirdCMD
#
# setghm (c) 2025
#
# Generate a self-extracting Cabinet file.
#
# Setup in post-build events:
# powershell "$(ProjectDir)Export-CAB.ps1" -ProjectDir $(ProjectDir) -TargetDir $(TargetDir) -ProjectName $(ProjectName)
#
param(
	[Parameter(Mandatory=$true)][string]$TargetDir,
	[Parameter(Mandatory=$true)][string]$ProjectDir,
	[Parameter(Mandatory=$true)][string]$ProjectName
)

$ExportName = "flappy"
$ExportCabName = "$ExportName.cab"
$ExportExeName = "$ExportName.exe"
$ExportDirectiveFile = "directives.ddf"

$AutoExtractProgram = "$env:WINDIR\System32\extrac32.exe"

# Work on the build directory.
Set-Location $TargetDir

# Get assets folder contents.
$AssetsDir = "$($ProjectDir)assets"
$AssetsList = Get-ChildItem $AssetsDir | ForEach-Object { "$AssetsDir\$($_.Name)" }

# Create the cabinet directive file contents.
$CabinetDirectiveFile = @"
; Generated MakeCAB directive file
;
.OPTION EXPLICIT

.Set CabinetNameTemplate=$ExportCabName
.Set DiskDirectoryTemplate=.
.Set CompressionType=MSZIP
.Set Cabinet=on
.Set Compress=on

$TargetDir$ProjectName.exe

.Set DestinationDir=assets
$($AssetsList -join "`r`n")
"@

# Save Cabinet directive file.
$CabinetDirectiveFile | Out-File -Encoding utf8 -FilePath $ExportDirectiveFile

# Generate the Cabinet file on the build directory.
MakeCAB /F $ExportDirectiveFile

# Generate the self-extracting Cabinet file.
Get-Content $AutoExtractProgram,$ExportCabName -Encoding Byte | Set-Content $ExportExeName -Encoding Byte
