Write-Host "==============================="
Write-Host "      C Program Downloader"
Write-Host "==============================="
Write-Host ""

# Base URL of your GitHub repo (raw content)
$repoBase = "https://raw.githubusercontent.com/ashleyxdev/dsa-suite/master"

# List available C programs (add or remove as needed)
$cPrograms = @(
    @{ id = 1; name = "college-graph-bfs-dfs.c" },
    @{ id = 2; name = "city-graph-dijkstra.c" },
    @{ id = 3; name = "hash-map.c" },
    @{ id = 4; name = "threaded-binary-tree.c" },
    @{ id = 5; name = "knapsack-fractional-and-01.c" },
    @{ id = 6; name = "bellman-ford.c" },
    @{ id = 7; name = "n-queens.c" },
    @{ id = 8; name = "travelling-salesman-branch-bound.c" },
    @{ id = 9; name = "floyd-warshall.c" },
    @{ id = 10; name = "01-knapsack-branch-bound.c" }
)

# Display options
Write-Host "Available C Programs:`n"
foreach ($p in $cPrograms) {
    Write-Host "$($p.id). $($p.name)"
}

Write-Host ""
$choice = Read-Host "Enter your choice (1-$($cPrograms.Count))"

$selected = $cPrograms | Where-Object { $_.id -eq [int]$choice }

if (-not $selected) {
    Write-Host "Invalid choice! Exiting."
    exit
}

# Download chosen C program
$fileUrl = "$repoBase/$($selected.name)"
Write-Host "`nDownloading $($selected.name)..."
try {
    Invoke-WebRequest -Uri $fileUrl -OutFile $selected.name -ErrorAction Stop
    Write-Host "✅ Download complete! File saved as: $($selected.name)"
} catch {
    Write-Host "❌ Failed to download file. Please check the repository link or filename."
}

Write-Host "`nDone!"
