import serial
import threading
from flask import Flask, jsonify, render_template_string

app = Flask(__name__)
umidade = 0

# Configura a porta serial
try:
    ser = serial.Serial('COM5', 115200)  # Substitua 'COM5' pela sua porta serial
    print("Porta serial aberta com sucesso.")
except serial.SerialException as e:
    print(f"Erro ao abrir a porta serial: {e}")
    ser = None

def ler_serial():
    global umidade
    if ser:
        while True:
            if ser.in_waiting > 0:
                umidade = ser.readline().decode('utf-8').strip()
                print(f"Umidade lida: {umidade}")

# Inicia a thread para ler a porta serial
if ser:
    threading.Thread(target=ler_serial, daemon=True).start()
    print("Thread de leitura da porta serial iniciada.")

# Rota para retornar a umidade atual em formato JSON
@app.route('/umidade')
def get_umidade():
    global umidade
    print(f"Enviando umidade: {umidade}")
    return jsonify(umidade=umidade)

# Rota para a página principal
@app.route('/')
def home():
    return render_template_string('''
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Umidade Atual</title>
            <script>
                function atualizarUmidade() {
                    fetch('/umidade')
                        .then(response => response.json())
                        .then(data => {
                            document.getElementById('umidade').innerText = data.umidade;
                        })
                        .catch(error => console.error('Erro ao atualizar a umidade:', error));
                }
                setInterval(atualizarUmidade, 2000); // Atualiza a cada 2 segundos
            </script>
        </head>
        <body>
            <h1>Umidade Atual</h1>
            <p id="umidade">Carregando...</p>
        </body>
        </html>
    ''')

if __name__ == '__main__':
    print("Iniciando o servidor Flask...")
    app.run(debug=True)