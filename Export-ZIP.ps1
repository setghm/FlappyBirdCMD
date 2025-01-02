# Export file for FlappyBirdCMD
#
# setghm (c) 2025
#
# Generate a ZIP file.
#
# Setup in post-build events:
# powershell "$(ProjectDir)Export-ZIP.ps1" -ProjectDir $(ProjectDir) -TargetDir $(TargetDir) -ProjectName $(ProjectName)
#
param(
	[Parameter(Mandatory=$true)][string]$TargetDir,
	[Parameter(Mandatory=$true)][string]$ProjectDir,
	[Parameter(Mandatory=$true)][string]$ProjectName
)

$compress = @{
	Path = "$($ProjectDir)assets", "$($TargetDir)$ProjectName.exe"
	CompressionLevel = "Fastest"
	DestinationPath = "$($TargetDir)$ProjectName.zip"
}

# Generate the ZIP file on the build directory.
Compress-Archive -Force @compress
