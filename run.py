import subprocess
import time

def param(type, start, end, heur=42):
    if heur == 42:
        for test in range(start, end + 1):
            for h in range(4):
                subprocess.run(['./main', f'{type}{test}', str(h)])
                time.sleep(1)
            print("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------")
    else:
        for i in range(start, end + 1):
            subprocess.run(['./main', f'{type}{i}', str(heur)])
            time.sleep(1)

# Example usage:
param('A', 1, 10, 42)
