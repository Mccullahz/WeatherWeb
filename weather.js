
    document.getElementById('weatherForm').addEventListener('submit', function(event) {
        event.preventDefault();
        var city = document.getElementById('city').value;
        fetch(API_URL + city + '&appid=' + API_KEY)
            .then(response => response.json())
            .then(data => {
                document.getElementById('weatherData').innerHTML = 
                    'Weather Data for ' + city + ': ' + JSON.stringify(data);
            })
            .catch(error => console.error('Error:', error));
    });


