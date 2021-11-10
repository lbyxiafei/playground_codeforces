$title = $args[0]

Write-Host "Commiting..."
git add .
git commit -m $title
git status
Write-Host "Commiting...Done!"
