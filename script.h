#!/bin/bash

# Your GitHub access token (replace with your own token)
token="YOUR_GITHUB_TOKEN"

# Your GitHub username
github_username="your_username"

# Get the list of your GitHub repositories
repositories_json=$(curl -s -H "Authorization: token $token" "https://api.github.com/users/$github_username/repos")

# Parse the JSON response to extract repository names
repositories=($(echo "$repositories_json" | jq -r '.[].name'))

# Define an array to store the selected repository names
selected_repositories=()

# Define the whiptail options
whiptail_opts=(--title "Select Repositories" --checklist "Choose the repositories to clone:" 20 50 15)

# Watermark text
watermark="Script by Moealsir"

# Calculate the number of spaces to center the watermark
total_width=50
watermark_width=${#watermark}
left_spaces=$((($total_width - $watermark_width) / 2))
right_spaces=$(($total_width - $watermark_width - $left_spaces))

# Add spaces before and after the watermark to center it
centered_watermark="$(printf "%${left_spaces}s%s%${right_spaces}s" "" "$watermark" "")"

# Loop through the repository names and prepare the options
for repo_name in "${repositories[@]}"; do
    whiptail_opts+=("$repo_name" "" off)
done

# Show the checklist and store the selected repository names
selected_repo_names=$(whiptail "${whiptail_opts[@]}" 3>&1 1>&2 2>&3)

# Loop through the selected repository names and store them
for repo_name in $selected_repo_names; do
    # Remove double quotes from the repository name
    repo_name=$(sed 's/"//g' <<< "$repo_name")
    selected_repositories+=("$repo_name")
done

# Loop through the selected repositories and clone them
for repo_name in "${selected_repositories[@]}"; do
    repo_url="https://$token@github.com/$github_username/$repo_name.git"
    repo_path="./$repo_name"

    if [ -d "$repo_path" ]; then
        echo "Updating $repo_name..."
        cd "$repo_path"
        git pull
        cd - > /dev/null
    else
        echo "Cloning $repo_name..."
        git clone "$repo_url" "$repo_path"
    fi
done

# Add a centered watermark to the script message
whiptail --msgbox "$centered_watermark" 10 50

# Print a message indicating the cloning process is complete
echo "Selected repositories have been cloned or updated."

