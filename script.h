#!/bin/bash

# Your GitHub access token (replace with your own token)
token=""

# Get the script file name
script_file="${BASH_SOURCE[0]}"

# Function to change the GitHub username
change_github_username() {
    read -p "Enter your new GitHub username: " new_username
    sed -i "s/github_username=\"${github_username}\"/github_username=\"$new_username\"/" "$script_file"
    echo "GitHub username updated to: $new_username"
}

# Function to change the GitHub token
change_github_token() {
    read -p "Enter your new GitHub access token: " new_token
    sed -i "s/token=\"${token}\"/token=\"$new_token\"/" "$script_file"
    echo "GitHub token updated."
}

# Function to clone selected repositories
clone_repositories() {
    # Your GitHub username
    github_username="Moealsir"

    # Get the list of your GitHub repositories
    repositories_json=$(curl -s -H "Authorization: token $token" "https://api.github.com/users/$github_username/repos")

    # Parse the JSON response to extract repository names
    repositories=($(echo "$repositories_json" | jq -r '.[].name'))

    # Define an array to store the selected repository names
    selected_repositories=()

    # Define the whiptail options
    whiptail_opts=(--title "Select Repositories" --checklist "Choose the repositories to clone:" 20 50 15)

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

    echo "Selected repositories have been cloned or updated."
}

# Main menu
while true; do
    clear
    echo "GitHub Tools"
    echo "-----------------"
    echo "1. Change GitHub Username"
    echo "2. Change GitHub Token"
    echo "3. Clone Repositories"
    echo "4. Exit"
    read -p "Select an option: " choice

    case $choice in
        1)
            change_github_username
            read -p "Press Enter to continue..."
            ;;
        2)
            change_github_token
            read -p "Press Enter to continue..."
            ;;
        3)
            clone_repositories
            read -p "Press Enter to continue..."
            ;;
        4)
            echo "Exiting. Scripted by $(tput bold)Moealsir$(tput sgr0)."
            exit 0
            ;;
        *)
            echo "Invalid option. Please try again."
            ;;
    esac
done

