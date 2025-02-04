#!/bin/bash
TIEMPO_ESPERA_COMPILACION=0.5
# ------- Compilacion de utils --------
echo "compilandooo utilss..."
cd utils 
make clean 
make 
cd ..
echo "Fin de compilacion..."

## ------ Tmux y su magia ---------

touch  ~/.tmux.conf
# (eso te abre un editor de texto por consola)

echo "setw -g mouse on" > ~/.tmux.conf
# (escribi esa linea)


tmux new-session -d -s my_session

tmux source-file ~/.tmux.conf

tmux split-window -h
# Split window horizontally
tmux select-pane -t 0
tmux split-window -v

# Split the second pane vertically
tmux select-pane -t 2
tmux split-window -v

# Realizar comando en each pane 
## Orden de ejecucion CPU-KERNEL-Memoria-I/O
tmux send-keys -t 0 'cd memoria' Enter
tmux send-keys -t 0 'make clean' Enter
tmux send-keys -t 0 'echo memoria' Enter
tmux send-keys -t 0 'make' Enter
tmux send-keys -t 0 './bin/memoria memoria.config' Enter
sleep ${TIEMPO_ESPERA_COMPILACION} 

tmux send-keys -t 1 'cd cpu' Enter
tmux send-keys -t 1 'make clean' Enter
tmux send-keys -t 1 'echo "CPU"' Enter
tmux send-keys -t 1 'make' Enter
tmux send-keys -t 1 './bin/cpu cpu.config' Enter
sleep ${TIEMPO_ESPERA_COMPILACION} 

tmux send-keys -t 2 'cd kernel' Enter
tmux send-keys -t 2 'make clean' Enter
tmux send-keys -t 2 'echo kenel' Enter
tmux send-keys -t 2 'make' Enter
tmux send-keys -t 2 './bin/kernel kernel.config' Enter
sleep ${TIEMPO_ESPERA_COMPILACION} 

tmux send-keys -t 3 'cd entradasalida' Enter
tmux send-keys -t 3 'make clean' Enter
tmux send-keys -t 3 'echo entradasalida' Enter
tmux send-keys -t 3 'make' Enter
tmux send-keys -t 3 './bin/entradasalida entradasalida.config' Enter


# Attach to the created session

tmux attach-session -t my_session
