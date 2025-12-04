C++ Authenticated Web App
A modern full-stack application demonstrating a powerful C++ backend with a RESTful API for authentication, paired with a beautiful and responsive React frontend built with Vite.

📸 Screenshot
(Add a screenshot of your login page and dashboard here)

Login Page
Dashboard Page

✨ Features
Secure C++ Backend: Built with C++20, featuring a local HTTP server (cpp-httplib).
Token-Based Authentication: Simple, secure login system that protects API endpoints.
Modern React Frontend: Clean, responsive UI built with React and Vite for a fast development experience.
RESTful API: Well-defined JSON API for communication between the frontend and backend.
Component-Based Architecture: Clean separation of concerns with reusable React components.
Professional Styling: Beautiful, gradient-based UI with smooth transitions and a glass-morphism effect.
🛠️ Technology Stack
Backend
Language: C++20
Build System: CMake
Libraries:
cpp-httplib: A simple C++ HTTP/HTTPS server and client library.
nlohmann/json: JSON for Modern C++.
Frontend
Framework: React 18
Build Tool: Vite
Language: JavaScript (JSX)
Styling: Vanilla CSS with CSS Variables
📋 Prerequisites
Before you begin, ensure you have the following installed on your system:

CLion IDE: Download here.
A C++ Compiler: MinGW (on Windows) or GCC/Clang (on Linux/macOS). CLion usually helps you set this up.
Node.js and npm: Download here. This is for the React frontend.
Git: Download here.
🚀 Installation and Setup
Follow these steps to get a copy of the project up and running on your local machine.

1. Clone the Repository
   bash

Line Wrapping

Collapse
Copy
1
2
git clone https://github.com/YourUsername/CppAuthApp.git
cd CppAuthApp
2. Backend Setup (C++)
   Open the CppAuthApp folder in CLion.
   CLion will prompt you to open the project as a CMake project. Click "Open".
   CLion will automatically run the CMake configuration, downloading the necessary C++ libraries (cpp-httplib, nlohmann/json). Wait for this to complete.
3. Frontend Setup (React)
   Open a separate terminal (not the CLion terminal).
   Navigate into the frontend directory:
   bash

Line Wrapping

Collapse
Copy
1
cd frontend/app
Install the required Node.js dependencies:
bash

Line Wrapping

Collapse
Copy
1
npm install
🏃‍♂️ Running the Application
This application requires two servers to be running simultaneously.

1. Start the C++ Backend
   In CLion, click the green Run 'CppAuthApp' button.
   The backend server will start on http://localhost:8080.
   Leave this console window open.
2. Start the React Frontend
   In your separate terminal (still in frontend/app), run the development server:
   bash

Line Wrapping

Collapse
Copy
1
npm run dev
The frontend server will start on http://localhost:5173.
Leave this terminal window open.
3. Access the Application
   Open your web browser and navigate to http://localhost:5173.
   You will see the login page.
   📖 Usage
   Log In: Use the following credentials to access the protected dashboard.
   Username: admin
   Password: password123
   Access Dashboard: Upon successful login, you will be redirected to the dashboard, which displays data fetched securely from the C++ backend.
   Logout: Click the "Logout" button to clear your session and return to the login page.
   📁 Project Structure

Line Wrapping

Collapse
Copy
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
CppAuthApp/
├── .gitignore              # Specifies files for Git to ignore
├── CMakeLists.txt          # CMake build configuration
├── main.cpp                # C++ backend server code
├── README.md               # This file
└── frontend/               # React application
└── app/
├── dist/            # Production build of React app (served by C++)
├── node_modules/    # Node.js dependencies
├── public/          # Static assets
├── src/             # React source code
│   ├── App.jsx
│   ├── Dashboard.jsx
│   ├── Login.jsx
│   ├── index.css
│   └── main.jsx
├── package.json
└── vite.config.js
🔗 API Endpoints
POST /api/login
Authenticates a user and returns a token.

Request Body:
json

Line Wrapping

Collapse
Copy
1
2
3
4
⌄
{
"username": "admin",
"password": "password123"
}
Success Response (200 OK):
json

Line Wrapping

Collapse
Copy
1
2
3
4
⌄
{
"message": "Login successful",
"token": "my-super-secret-token-12345"
}
Error Response (401 Unauthorized):
json

Line Wrapping

Collapse
Copy
1
2
3
⌄
{
"error": "Invalid credentials"
}
GET /api/dashboard
Returns protected data for the authenticated user.

Request Headers:

Line Wrapping

Collapse
Copy
1
Authorization: Bearer my-super-secret-token-12345
Success Response (200 OK):
json

Line Wrapping

Collapse
Copy
1
2
3
4
5
6
7
8
⌄
⌄
{
"user": "Authenticated User",
"data": [
"Welcome to the dashboard!",
"This is protected data.",
"Here are your stats: 42"
]
}
Error Response (401 Unauthorized):
json

Line Wrapping

Collapse
Copy
1
2
3
4
⌄
{
"error": "Unauthorized",
"message": "Invalid or missing token"
}
🚀 Future Enhancements
Implement React Router for a more complex single-page application.
Replace the in-memory user map with a real database (e.g., SQLite, PostgreSQL).
Implement password hashing for secure credential storage.
Add more API endpoints for user management and data manipulation.
Containerize the application with Docker for easy deployment.
📄 License
This project is licensed under the MIT License. See the LICENSE file for details.



