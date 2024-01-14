# Iterate from 1 to 10 and call make run with arg=x
param (
    [char]$type,
    [int]$start,
    [int]$end,
    [int]$heur = 0
)

# $Host.UI.RawUI.ForegroundColor = [System.ConsoleColor]::White

for ($i = $start; $i -le $end; $i++) {
    & ./main $type$i $heur
    Start-Sleep -Milliseconds 1000 # Add a half-second (500 milliseconds) delay
}
# .\script.ps1 -type 'c' -start 1 -end 10 -heur 1
# Set-ExecutionPolicy -Scope Process Bypass