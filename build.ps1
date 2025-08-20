$skseDir = "./skse"
$targetDir = "D:\RfaD SE\MO2\mods\RfaD Oil Widget\SKSE\Plugins"
$uiDir = "./ui"
$uiTargetDir = "D:\RfaD SE\MO2\mods\RfaD Oil Widget\PrismaUI\views"

# Build SKSE plugin
Set-Location $skseDir
xmake -y -w
Copy-Item -Path "./build/windows/x64/release/RfaD-Oil-Widget.dll" -Destination $targetDir -Force

# Build UI
Set-Location ../
Set-Location $uiDir
npm run generate

Remove-Item -Path "./dist/200.html" -Force -ErrorAction SilentlyContinue
Remove-Item -Path "./dist/404.html" -Force -ErrorAction SilentlyContinue

Copy-Item -Path "./dist/*" -Destination $uiTargetDir -Recurse -Force

# Return to original directory
Set-Location -Path ".."

# Print completion message
Write-Host "
Build completed and files copied successfully."