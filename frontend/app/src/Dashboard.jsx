import React, { useState, useEffect } from 'react';

function Dashboard({ token, onLogout }) { // --- RECEIVE onLogout AS A PROP ---
    const [data, setData] = useState(null);
    const [error, setError] = useState('');

    useEffect(() => {
        const fetchProtectedData = async () => {
            try {
                const response = await fetch('/api/dashboard', {
                    headers: { 'Authorization': `Bearer ${token}` },
                });

                if (response.ok) {
                    const result = await response.json();
                    setData(result);
                } else {
                    setError('Failed to fetch protected data.');
                }
            } catch (err) {
                setError('An error occurred.');
            }
        };

        fetchProtectedData();
    }, [token]);

    // --- USE THE PROP FOR THE ONCLICK HANDLER ---
    const handleLogoutClick = () => {
        onLogout(); // Call the function passed down from App
    };

    return (
        <div>
            <h2>Dashboard</h2>
            {/* --- USE THE NEW HANDLER --- */}
            <button onClick={handleLogoutClick}>Logout</button>
            {error && <p style={{ color: 'red' }}>{error}</p>}
            {data && (
                <div>
                    <p><strong>Welcome:</strong> {data.user}</p>
                    <ul>
                        {data.data.map((item, index) => (
                            <li key={index}>{item}</li>
                        ))}
                    </ul>
                </div>
            )}
        </div>
    );
}

export default Dashboard;