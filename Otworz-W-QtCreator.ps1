# Otwiera projekt w Qt Creator (CMake + preset qt6-debug).
$ErrorActionPreference = "Stop"
$ProjectRoot = $PSScriptRoot
$CMakeLists = Join-Path $ProjectRoot "CMakeLists.txt"

if (-not (Test-Path $CMakeLists)) {
    Write-Error "Brak pliku CMakeLists.txt w: $ProjectRoot"
}

$CreatorCandidates = @(
    $env:QTCREATOR_PATH,
    "$env:USERPROFILE\Qt\Tools\QtCreator\bin\qtcreator.exe",
    "C:\Qt\Tools\QtCreator\bin\qtcreator.exe",
    "C:\Qt\Tools\QtCreator\bin\qtcreator.cmd"
) | Where-Object { $_ -and (Test-Path $_) }

$QtCreator = $CreatorCandidates | Select-Object -First 1
if (-not $QtCreator) {
    Write-Host "Nie znaleziono Qt Creator." -ForegroundColor Red
    Write-Host "Zainstaluj Qt (z qt.io) albo ustaw zmienna QTCREATOR_PATH, np.:"
    Write-Host '  $env:QTCREATOR_PATH = "C:\Qt\Tools\QtCreator\bin\qtcreator.exe"'
    exit 1
}

$userPresets = Join-Path $ProjectRoot "CMakeUserPresets.json"
$examplePresets = Join-Path $ProjectRoot "CMakeUserPresets.json.example"
if (-not (Test-Path $userPresets) -and (Test-Path $examplePresets)) {
    Copy-Item $examplePresets $userPresets
    Write-Host "Utworzono CMakeUserPresets.json - sprawdz sciezke do Qt (CMAKE_PREFIX_PATH)." -ForegroundColor Yellow
}

Write-Host "Uruchamiam Qt Creator: $QtCreator"
Start-Process -FilePath $QtCreator -ArgumentList $CMakeLists
