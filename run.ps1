param (
    [char]$type,
    [int]$start,
    [int]$end,
    [int]$heur = 42
)
if ($heur -eq 42) {

    for ($test = $start; $test -le $end; $test++) {
        for ($h = 0; $h -le 3; $h++) {
            & ./main $type$test $h
            Start-Sleep -Milliseconds 1000
        }
        Write-Host "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
    }
}
else {
    for ($i = $start; $i -le $end; $i++) {
        & ./main $type$i $heur
        Start-Sleep -Milliseconds 1000
    }
}

# .\run.ps1 -type 'c' -start 1 -end 10 -heur 1 

# Set-ExecutionPolicy -Scope Process Bypass