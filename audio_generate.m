% 
% Huanle Zhang at UC Davis. www.huanlezhang.com
% June 8, 2017

% Generate source and header files for Bare Metal

clear,clc

t = 10; % 
t_skip = 5;

[audio_data, Fs] = audioread('audio_1.m4a');

Fs_target = 37037;

audio_data = audio_data(:,1);

audio_data = audio_data(Fs*t_skip:end);

audio_data = resample(audio_data, Fs, Fs_target);

audio_data = audio_data(1:Fs_target*t);

audio_data = (audio_data + 1) / 2 * 255;

audio_data = uint8(audio_data);

% audio_data = uint8(floor(255 * rand(size(audio_data))));

fileID = fopen('audio_1.c', 'w');
fileID_H = fopen('audio_1.h','w');

fprintf(fileID_H, '#ifndef _AUDIO_DATA_1_H\n#define _AUDIO_DATA_1_H\n#define AUDIO_1_LEN %d\n', length(audio_data));
fprintf(fileID_H, 'extern char audio_data1[];\n#endif');
fprintf(fileID, 'char audio_data1[] = {\n');
for i = 1:length(audio_data)-1
    fprintf(fileID, '\t%d,\n', audio_data(i));
end
fprintf(fileID, '\t%d\n', audio_data(end));
fprintf(fileID, '};');
fclose(fileID);
fclose(fileID_H);