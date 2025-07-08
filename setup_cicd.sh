# setup_cicd.sh
#!/bin/bash

echo "Setting up CI/CD files..."

# Create directories
mkdir -p .github/workflows
mkdir -p .github

# Create dependabot.yml
cat > .github/dependabot.yml << 'EOF'
version: 2
updates:
  - package-ecosystem: "github-actions"
    directory: "/"
    schedule:
      interval: "weekly"
    open-pull-requests-limit: 5
EOF

# Create .gitignore
cat > .gitignore << 'EOF'
# Build directories
build/
build_*/
*build*/
twister-out*/
coverage_report/

# IDE files
.vscode/
.idea/
*.swp
*.swo
*~

# OS files
.DS_Store
Thumbs.db

# Python
__pycache__/
*.py[cod]
*$py.class
*.so
.Python
env/
venv/

# Coverage files
*.gcov
*.gcda
*.gcno
*.info
htmlcov/
.coverage

# Docker
.dockerignore

# Temporary files
*.tmp
*.temp
*.log
EOF

echo "✅ Dependabot and .gitignore created"
echo "Now copy the CI workflow files from the artifacts above to:"
echo "  - .github/workflows/ci.yml"
echo "  - .github/workflows/docker-build.yml" 
echo "  - .github/workflows/codeql.yml"