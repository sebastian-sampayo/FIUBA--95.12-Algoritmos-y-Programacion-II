% ------------------------------------------------------------------------------
% Algoritmos y Programación II
% TP0
% Simulación de Modulación y Demodulación FM

% 	Este script toma los primeros 'T' segundos de un archivo de sonido
% y lo modula en frecuencia sobre una portadora 'fc'.
% 	Luego demodula la señal obtenida y la reproduce con la placa de sonido.
% -- Versión modificada:
% Opero primero, y decimo en 44 directamente.
% ------------------------------------------------------------------------------

clear all;
close all;

%% Cargo la señal de audio de entrada
input_filename = '71. Mary Ann.flac';
[input_audio, fs] = audioread(input_filename);
str = sprintf('La frecuencia de muestreo FS es: %i', fs);
disp(str)
 
%% Me quedo con T segundos de un solo canal (monofónico)
T = 5;
input_audio = input_audio(1:fs*T,1);
input_audio_length = fs*T;

% -----------------------------------------------------------------------------
%% Modulación
% -----------------------------------------------------------------------------
% Para simular una modulación en FM 
% se debe subir la frecuencia de muestreo:
%% Interpolación, sobremuestreo x44
m = interp(input_audio, 44);
m_length = length(m);

%% Calculo la integral discreta
M = cumsum(m);

%% Señal FM modulada final:
fc = 4.2e6;
n = (1:m_length)';
w = 2*pi*fc;
s_fm = exp(j*(w*n + M)); % Esta es la señal que iría a la entrada del TP0

% -----------------------------------------------------------------------------
%% Demodulación
% -----------------------------------------------------------------------------
% En este caso, primero opero para obtener la diferenciación de la fase
% y luego realizo la decimación, así no hay pérdida de calidad.
x = s_fm;

%% Desplazamiento en 1 unidad, x(n-1)
x_delay = [0; x(1:end-1)];

%% Operación para obtener la diferenciación de la fase
x2 = x .* conj(x_delay);
phase = angle(x2);

%% Promedio móvil de 44 muestras
h = 1/44 * ones(44,1);
phase = filter(h,1,phase);

%% Decimacion por 44
m_demod = decimate(phase, 44);

%% Salida
output = m_demod/max(m_demod) * 0.5;
sound(output, fs);

%% Graficos
% cols = 3;
% fils = 2;
% figure(1)
% subplot(fils,cols,1)
% plot(input_audio)
% title('Audio original (input_audio)');
% subplot(fils,cols,4)
% plot(M)
% title('Integral de la señal de Audio original (M) -fase de la señal a transmitir-');
% subplot(fils,cols,2)
% plot(real(s_fm(1:end)))
% title('Señal a transmitir (s_fm) -parte real-');
% subplot(fils,cols,5)
% plot(imag(s_fm(1:end)))
% title('Señal a transmitir (s_fm) -parte imaginaria-');
% subplot(fils,cols,3)
% plot(phase)
% title('Fase de la señal recibida (phase)');
% subplot(fils,cols,6)
% plot(output)
% title('Salida');
