function [compr,active,inactive,divisions,misdet,falsealarm] = funcSFD(s,Fs,nbits,ref,SNR)

% PARAMETERS
k = 1;
imax = Fs*20*10^(-3)%no of samples per frame
non_voice_th = 14;%n;if 14 frames has e>eth/var(dct(e))>varth,considered vocie

p=0.136;

if(SNR>27.5)
    p=0.15;
elseif((SNR<=27.5)&(SNR>22.5))
    p=0.136;
elseif((SNR<=22.5)&(SNR>18.5))
    p=0.12;
  elseif((SNR<=18.5)&(SNR>12.5))
    p=0.105;
   elseif((SNR<=12.5)&(SNR>7.5))
    p=0.087;
    elseif((SNR<=7.5)&(SNR>2.5))
    p=0.063;
    elseif((SNR<=2.5))
    p=0.003;
end





compr=0;
active=0;
inactive=0;
misdet=0;
falsealarm=0;
f = s;% EQUATE F TO S
len = numel(f);%Number of samples of the audio signal;Here f==s
disp(len);

% ADJUSTING THE THRESHOLD
% non_voice_th = floor (non_voice_th*Fs/44100);%settinghow many 'n';but Fs=44100;hence non_voice_th=14 itself

divisions=floor(len/imax);%gives us the no of framess!!
zcr = zeros(divisions,1);% gives 6(diisions)x1 matrix with 000000.....00
voice_flags = zeros(divisions,1);
frame = zeros(imax+1,1);
variance=zeros(divisions,1);
voice_flags=zeros(divisions,1);


%var_th= 100000000*var((dct(f(1:500))))%multiply by 10 just in case;finding thrshold in white noise(doing DCT)
%k=850;
%var_th=k*0.0001;%THIS THRESHOLD WAS SET BY OBSERVING THE VARIANCE BY TRIAL AND ERROR
K=1.028;
var_th=K*var(dct(f(1:100)));
var_th=K*6.2569e-04
%var_th=K*10095.69e-04
non_voice_count = 1;
output = [];
pause on;

for i=1:divisions % from first frame to last frame
    if imax*i > len %condition to check if reached last frame
        break
    end
    frame(2:end,1) = f(imax*(i-1)+1:imax*i);
    
    temp_size = size( find(frame(2:end).*frame(1:end-1) < 0));
    zcr(i) = temp_size(1);%GIVES NO OF ZERO CROSSINGS
    variance(i)=var(dct(frame));
    
    if(variance(i) < var_th)
         var_th=(1-p)*var_th+p*variance(i);
         voice_flags(i)=0; 
         compr=compr+1;
         inactive=inactive+1;
    end
    
    if(variance(i) >= var_th)
        voice_flags(i)=1;
        active=active+1;
                 
    end
end


max(variance)


for i = 1:divisions
    if (voice_flags(i) == 1)
        output = [output;ones(imax,1)];%whereever there is voice cascade 1's (like appending);so we can see where voice is there
    else
        output = [output;zeros(imax,1)];
    end
end
min_size = min(size(f), size(output));
output_mask =  output(1:min_size);%max value*wherever there is one; to amplify the signal which shows where voice present


for i=1:divisions
     if((voice_flags(i)==0)&(ref(i)==1))
        misdet=misdet+1;
        end
end


for i=1:divisions
     if((voice_flags(i)==1)&(ref(i)==0))
        falsealarm=falsealarm+1;
        end
end
falsealarm=(falsealarm/divisions)*100;
misdet=(misdet/divisions)*100;
% 
% figure;plot(f,'b');
%  hold on;
%  plot(output_mask, 'r');
%  hold on;
%  
compr=((compr/divisions)*100);
if max(output_mask) ~= 0
    disp('Conclusion : Signal contains voice.');
else 
    disp('Conclusion : Signal does not contain voice.');
end
