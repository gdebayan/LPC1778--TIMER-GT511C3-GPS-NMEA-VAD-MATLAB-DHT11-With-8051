
%[x,R, nbits] = wavread('C:\Users\AYAN\AppData\Roaming\MathWorks\MATLAB\check.wav'); % Read in a wave file the syntax x=file;R=samplerate;nbits = nbit of data
clear all;
close all;
clc;

% PARAMETERS
k = 1;
imax = 500;%no of samples per frame
non_voice_th = 14;%n;if 14 frames has e>eth,considered vocie

p=0.002;
m=20;%buffer for 'm' silent frames
buffer=zeros(20,1);
compr=0;



% TAKING USER INPUT FOR FILE PATH
path = input('Please provide the path of the folder (should not contain blank spaces): ','s');
filename = input('Please provide the filename of audio file (with extension): ','s');




%strRead = strcat(path, '/', 'output.wav');
strRead = strcat(path, '/', filename);
[s, Fs, nbits] = wavread(strRead);
disp(Fs);
disp(nbits);

% THIS IS DONE FOR STEREO SIGNALS
f = s;% equating f to s
len = numel(f);%Number of samples of the audio signal;Here f==s
disp(len);

% ADJUSTING THE THRESHOLD
non_voice_th = round (non_voice_th*Fs/44100);%settinghow many 'n';but Fs=44100;hence non_voice_th=14 itself

divisions=round(len/imax);%gives us the no of framess!!
zcr = zeros(divisions,1);% gives 6(diisions)x1 matrix with 000000.....00
energy = zeros(divisions,1);%initial energy of all the frames is 0
voice_flags = zeros(divisions,1);
frame = zeros(imax+1,1);

min_energy = max(f(1:100));%take initial 100 samples(assuming no sound,only noice,and find the max energy,this will be threshold)
avg_begin = min(find(f > min_energy));%finds the INDEX with energy greater than min_energy min(find(n>2))->finds the index of n which is least for n>2

f_new=[];

%E_th = k*sum(f(avg_begin:end).*f(avg_begin:end))/(len-avg_begin);%k is scaling factor;defined as 1 before
E_th = 100*sum((f(1:100).*f(1:100)));
E_th=E_th/100;
%finds threshold energy
non_voice_count = 0;
output = [];
pause on;

variance1=10^(-24);%assign some initial value,preferably low
variance2=0;
count=1%to check the buffer
for i=1:divisions % from first frame to last frame
    if imax*i > len %condition to check if reached last frame
        break
    end
    frame(2:end,1) = f(imax*(i-1)+1:imax*i);%DONE TO DETECT ZCD
   
    temp_size = size( find(frame(2:end).*frame(1:end-1) < 0));
    zcr(i) = temp_size(1);%GIVES NO OF ZERO CROSSINGS
    energy(i) = sum(frame.*frame)/imax;   %ENERGY OF INDIVIDUAL FRAME
    
    
    if(energy(i) < E_th)
         E_th=(1-p)*E_th + p*energy(i);
     %    f_new=[f_new ,zeros(1,length(frame)-1)];
         voice_flags(i)=0;
         compr=compr+1;
         if(count < m)  %buffer 
             
            buffer(count)=energy(i);%keep adding to buffer
            count=count+1;
           
         elseif(count>=m)
             variance2=var(buffer);
            
             
             %check if variance2>variance1
            count=1;
            
            if(variance2>variance1)
                
                if((variance2/variance1>=1)&(variance2/variance1<=1.10))
                    p=0.0010;
                     
                elseif((variance2/variance1>1.10)&(variance2/variance1<=1.25))
                    p=0.0020;
                       
                 elseif((variance2/variance1>1.25)&(variance2/variance1<=2))
                     p=0.0025;
                        
                else
                    p=0.0010;
                    
                end
             
          
            end
              
         
         end 
       
        variance1=variance2;
         
    end
     
    if(energy(i) > E_th)
        %voice_flags(i)=1;
         %f_new=[f_new f(imax*(i-1)+1:imax*i)];
        non_voice_count = non_voice_count + 1;
        
          %elseif(non_voice_count ~= 0)
        if(non_voice_count > non_voice_th)
           %MAKE SURE 14 CONSECUTIVE FRAMES HAVE VOICE
            for k=1:non_voice_count
                voice_flags(i-k)=1;
                
            end
        
            
               
         end
        
    else
        non_voice_count = 0;          
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


% GENERATING THE PLOTS (OPTIONAL)
 figure;plot(f,'b');
 hold on;
 plot(output_mask, 'r');
 hold on;
 plot(sqrt(E_th).*ones(size(output_mask)),'c');%PLOT Ethreshold
%sound(f,Fs);
disp((compr/divisions)*100);
%sound(f_new,Fs);
if max(output_mask) ~= 0
    disp('Conclusion : Signal contains voice.');
else 
    disp('Conclusion : Signal does not contain voice.');
end