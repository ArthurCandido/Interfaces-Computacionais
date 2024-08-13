function fetchData() {
    fetch('/status')
        .then(response => response.text())
        .then(data => {
            const umidadeElement = document.getElementById('umidade');
            const statusElement = document.getElementById('status');
            
            if (data === 'Sim') {
                umidadeElement.textContent = 'Umidade Baixa!';
                statusElement.textContent = 'A bomba de água foi ativada.';
                statusElement.className = 'status status-low';
            } else if (data === 'Não') {
                umidadeElement.textContent = 'Umidade Adequada';
                statusElement.textContent = 'Tudo está certo.';
                statusElement.className = 'status status-ok';
            } else {
                umidadeElement.textContent = 'Erro ao carregar dados';
                statusElement.textContent = '';
                statusElement.className = 'status';
            }
        })
        .catch(error => {
            console.error('Erro ao buscar dados:', error);
            document.getElementById('umidade').textContent = 'Erro de conexão';
            document.getElementById('status').textContent = '';
        });
}

setInterval(fetchData, 2000);