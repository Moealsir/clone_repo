# GitHub Repository Cloning Script

This script allows you to select and clone your GitHub repositories. It uses Whiptail for a user-friendly interface and is designed to be easy to use, Also use your token for authentication.

## News
#### !!Run script using `sudo` to avoid permission issues.!! <br>

	- Added a new feature to modify token without re-running the script.
	- Added a new feature to modify username without re-running the script.
	
## Prerequisites

Before using this script, make sure you have the following:

- A GitHub access token for authentication (replace `YOUR_GITHUB_TOKEN` with your token).
- Your GitHub username (replace `your_username` with your username).
- The `jq` command-line tool for parsing JSON. You can install it on most systems.

## Installation
1. install `jq` using this command
	```
	sudo apt-get install jq
	```
2. Change 'srcipt.h' name to any alias you want to use for the script for example `cr`, which stands for clone repository.
3. Make the script executable.
4. Copy the script to your bin directory using command
	```
	sudo cp cr /bin/
	```
5. Call the script inside the directory you want to clone the repository to.