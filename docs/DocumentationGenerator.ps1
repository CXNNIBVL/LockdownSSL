$Except = @("index.md", "Documentation.md");

$text = "# Documentation`n***`n"

$names = [System.Collections.ArrayList]@()

foreach($file in (gci "./*.md"))
{
    if(!($Except.Contains($file.name)))
    {
        $name = $file.Basename
        $names.Add($name)
    }
}

$names = $names | sort

foreach($name in $names)
{
    $text += "* [$name](./$name.md)`n"
}

Set-Content -Path "./Documentation.md" -Value $text