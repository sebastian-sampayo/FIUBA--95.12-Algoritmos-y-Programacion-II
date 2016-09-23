% ------------------------------------------------------------------------------
% Algoritmos y Programación II
% TP0
% Simulación de Modulación FM

% 	Este script toma los primeros 'T' segundos de un archivo de sonido
% y lo modula en frecuencia sobre una portadora 'fc'
% Los formatos de entrada admitidos son:
% - WAV
% - FLAC
% - OGG
% - MP3
% - MP4
% La salida es un archivo de texto ASCII con el formato especificado en el TP0:
% (Real, Imag) (Real, Imag) (Real, Imag)...
% ------------------------------------------------------------------------------

clear all;

% ------------------------------------------------------------------------------
% Parámetros:
input_filename = '71. Mary Ann.flac';
output_filename_ascii = 'test_FM_ascii.txt';
T = 3; % [s]
fc = 4.2e6; % [Hz]
% ------------------------------------------------------------------------------


%% Cargo la señal de audio de entrada
[input_audio, fs] = audioread(input_filename);
str = sprintf('La frecuencia de muestreo FS es: %i', fs);
disp(str)
 
%% Me quedo con T segundos de un solo canal (monofónico)
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
n = (1:m_length)';
w = 2*pi*fc;
s_fm = exp(j*(w*n + M)); % Esta es la señal que iría a la entrada del TP0


%% Salida de texto en formato ASCII:
out_file_id = fopen(output_filename_ascii, 'w');
fprintf(out_file_id, '(%f,%f) ', real(s_fm), imag(s_fm));
fclose(out_file_id);



