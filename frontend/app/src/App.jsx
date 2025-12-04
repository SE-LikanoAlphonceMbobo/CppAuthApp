import React, { useState, useEffect } from 'react';
import Login from './Login';
import Dashboard from './Dashboard';

function App() {
    const [token, setToken] = useState(null);

    // On component mount, check if a token is in localStorage
    useEffect(() => {
        const storedToken = localStorage.getItem('authToken');
        if (storedToken) {
            setToken(storedToken);
        }
    }, []);

    const handleLogin = (authToken) => {
        setToken(authToken);
        localStorage.setItem('authToken', authToken);
    };

    // --- ADD THIS FUNCTION ---
    const handleLogout = () => {
        setToken(null); // Clear the token from React state
        localStorage.removeItem('authToken'); // Clear the token from localStorage
    };

    return (
        <div style={{ padding: '20px' }}>
            {token ? (
                // --- PASS THE LOGOUT FUNCTION AS A PROP ---
                <Dashboard token={token} onLogout={handleLogout} />
            ) : (
                <Login onLogin={handleLogin} />
            )}
        </div>
    );
}

export default App;