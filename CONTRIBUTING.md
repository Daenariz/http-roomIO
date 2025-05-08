## Development  

- The `develop` branch is the central working branch.  
- **Feature branches** must branch off from `develop`. 
```
# Before starting
git fetch --all
git checkout develop
git pull origin develop
git checkout -b feature/awesome-feature

# When you changes are ready to be uploaded
git add .
git commit -m "feat: short feature description"
git push origin feature/awesome-feature
```
- **Pull Requests** to `develop` require:  
  - 1 approved review  
  - Passing CI tests  
  - No merge conflicts  
- See [Git Flow](https://nvie.com/posts/a-successful-git-branching-model/).  
