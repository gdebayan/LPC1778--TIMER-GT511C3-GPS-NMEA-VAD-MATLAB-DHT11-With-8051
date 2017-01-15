function [compr,active,inactive,divisions,misdet,falsealarm] = funcZCD(s,Fs,nbits,ref)

% PARAMETERS
k = 1;
imax = Fs*20*10^(-3);%no of samples per frame
non_voice_th = 5;%n;if 14 frames has e>eth,considered vocie

p=0.00;

misdet=0;
falsealarm=0;

disp(Fs);
disp(nbits);
compr=0;
active=0;
inactive=0;

f = s;% EQUATING S TO F
len = numel(f);%Number of samples of the audio signal;Here f==s
disp(len);

% ADJUSTING THE THRESHOLD
non_voice_th = round (non_voice_th*Fs/44100);%settinghow many 'n';but Fs=44100;hence non_voice_th=14 itself

divisions=floor(len/imax);%gives us the no of framess!!
zcr = zeros(divisions,1);% gives 6(diisions)x1 matrix with 000000.....00
energy = zeros(divisions,1);%initial energy of all the frames is 0
voice_flags = zeros(divisions,1);
frame = zeros(imax+1,1);

min_energy = max(f(1:100));%take initial 100 samples(assuming no sound,only noice,and find the max energy,this will be threshold)
avg_begin = min(find(f > min_energy));%finds the INDEX with energy greater than min_energy min(find(n>2))->finds the index of n which is least for n>2
                                       %ABOVE LINE NOT REQUIRED

%E_th = k*sum(f(avg_begin:end).*f(avg_begin:end))/(len-avg_begin);%k is scaling factor;defined as 1 before
E_th=10*min_energy;
disp(E_th);
%finds threshold energy
non_voice_count = 0;
output = [];
pause on;

for i=1:divisions % from first frame to last frame
    if imax*i > len %condition to check if reached last frame
        break
    end
    frame(2:end,1) = f(imax*(i-1)+1:imax*i); %TAKEN FROM 2:END ->IN ORDER TO DETERMINE ZERO CROSSINGS
    temp_size = size( find(frame(2:end).*frame(1:end-1) < 0));
    zcr(i) = temp_size(1);%GIVES NO OF ZERO CROSSINGS
    energy(i) = sum(frame.*frame)/imax;   %ENERGY OF INDIVIDUAL FRAME
    %HERE COMPARING WRT ZCD
  
    
    if((zcr(i) >15)&(zcr(i)<74)) %here frame length = approx 10ms [500*[1/44000]]=11ms; range as specified in paper
        active=active+1;
    % THIS IF-ELSE LOOPDETERMINES IF 14(non_voice_th) CONSECUTIVE FRAMES
    % HAVE E>ETH;ONLY IF ITS SO TAKEN AS VOICE
        non_voice_count = non_voice_count + 1;
        
     voice_flags(i)=1;
       
        
    else
        non_voice_count = 0;  
        compr=compr+1;
        inactive=inactive+1;
    end
    
    
end

for i = 1:divisions
    if (voice_flags(i) == 1)
        output = [output;ones(imax,1)];%whereever there is voice cascade 1's (like appending);so we can see where voice is there
    else
        output = [output;zeros(imax,1)];
    end
end
min_size = min(size(f), size(output));
output_mask = output(1:min_size);%max value*wherever there is one; to amplify the signal which shows where voice present

for i=1:length(voice_flags)
     if((voice_flags(i)==0)&(ref(i)==1))
        misdet=misdet+1;
        end
end


for i=1:length(voice_flags)
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
compr=(compr/divisions)*100;
if max(output_mask) ~= 0
    disp('Conclusion : Signal contains voice.');
else 
    disp('Conclusion : Signal does not contain voice.');
end

end
