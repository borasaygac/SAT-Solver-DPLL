param (
    [char]$type,
    [int]$start,
    [int]$end,
    [int]$heur = 0
)

for ($i = $start; $i -le $end; $i++) {
    & ./main $type$i $heur
    Start-Sleep -Milliseconds 1000
}

# .\run.ps1 -type 'c' -start 1 -end 10 -heur 1

# Set-ExecutionPolicy -Scope Process Bypass