$title = $args[0]
$branch= &git rev-parse --abbrev-ref HEAD
$branch = "origin "+$branch
$date = Get-Date -Format s

if (!$title -or $title -eq ".") {
    $title = "Check point, " + $date + "."
}

Write-Host "Title:" $title
Write-Host "Branch:" $branch
Write-Host `n

gcommit $title

Write-Host "Pushing..."
git push $branch
Write-Host "Pushing...Done!"
