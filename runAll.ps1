param (
    [char]$type,
    [int]$start,
    [int]$end
)

# $Host.UI.RawUI.ForegroundColor = [System.ConsoleColor]::White

for ($i = $start; $i -le $end; $i++) {
    & ./main $type$i 0
    Start-Sleep -Milliseconds 1000

    & ./main $type$i 1
    Start-Sleep -Milliseconds 1000

    & ./main $type$i 2
    Start-Sleep -Milliseconds 1000

    & ./main $type$i 4
    Start-Sleep -Milliseconds 1000
}

# .\runAll.ps1 -type 'c' -start 1 -end 10

# Set-ExecutionPolicy -Scope Process Bypass