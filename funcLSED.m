function [compr,active,inactive,divisions,misdet,falsealarm] = funcLSED(s,Fs,nbits,ref)


% PARAMETERS
k = 1;
imax = Fs*20*10^(-3);%no of samples per frame
non_voice_th = 7;%n;if 14 frames has e>eth,considered vocie

p=0.3;
misdet=0;
falsealarm=0;
compr=0;
active=0;
inactive=0;


% THIS IS DONE FOR STEREO SIGNALS
f = s;% equating f to s
len = numel(f);%Number of samples of the audio signal;Here f==s
disp(len);
%dct1=dct(f);

divisions=floor(len/imax);%gives us the no of framess!!
zcr = zeros(divisions,1);% gives 6(diisions)x1 matrix with 000000.....00
energy = zeros(divisions,1);%initial energy of all the frames is 0
voice_flags = zeros(divisions,1);
frame = zeros(imax+1,1);
      dct2=dct(f(1:100));
       factor=round(1000*(length(dct2))/Fs);
      ene=sum(f(1:100).*f(1:100));
       if(sum(f(1:100).*f(1:100))>0.0001)
           k=10;
       else
           k=1000;
       end
       k=7
    E_th(1)=k*sum(dct2(1:factor).*dct2(1:factor));%sums of values from 0-1Khz
    E_th(2)=k*sum(dct2(factor+1:factor*2).*dct2(factor+1:factor*2));%sums of energy values from 1khz-2khz
    E_th(3)=k*sum(dct2(factor*2+1:factor*3).*dct2(factor*2+1:factor*3));%sums of values from 2khz-3khz
    E_th(4)=k*sum(dct2(factor*3+1:factor*4).*dct2(factor*3+1:factor*4));
    disp('ETHRESDH');
%    disp(E_th);
%k=0.2;
 %   E_th=k*0.0003.*ones(1,4);
    
  
energy_band=zeros(4);% no of frames X energy of each band(checking first 4 bands only!)


non_voice_count = 0; 
for i=1:divisions % from first frame to last frame
    if imax*i > len %condition to check if reached last frame
        break
    end
    frame(2:end,1) = f(imax*(i-1)+1:imax*i);%doing this to find ZCD
   
    temp_size = size( find(frame(2:end).*frame(1:end-1) < 0));
    zcr(i) = temp_size(1);%GIVES NO OF ZERO CROSSINGS
 
    dct2=dct(frame);
    ldct=length(dct2);
    
    factor=round(1000*ldct/Fs);% gives number of values within 0- 1kHz; 
   
  
    energy_band(1)=sum(dct2(2:factor).*dct2(2:factor));%sums of values from 0-1Khz
    energy_band(2)=sum(dct2(factor+1:factor*2).*dct2(factor+1:factor*2));%sums of energy values from 1khz-2khz
    energy_band(3)=sum(dct2(factor*2+1:factor*3).*dct2(factor*2+1:factor*3));%sums of values from 2khz-3khz
    energy_band(4)=sum(dct2(factor*3+1:factor*4).*dct2(factor*3+1:factor*4));
    
     
      
    
   if((energy_band(1) > E_th(1))&(((energy_band(2)>E_th(2))&(energy_band(3)>E_th(3)))|((energy_band(3)>E_th(3))&(energy_band(4)>E_th(4)))|((energy_band(2)>E_th(2))&(energy_band(4)>E_th(4)))))
           
     active=active+1;
        non_voice_count = non_voice_count + 1;
        
         voice_flags(i)=1;
       % if(non_voice_count > non_voice_th)
            %make sure 14 consecutive signals have voice
        %    for k=1:non_voice_count
        %        voice_flags(i-k)=1;
                
         %   end
        
            
               
          %  end
        
    else
        non_voice_count = 0;  
        compr=compr+1;
        inactive=inactive+1;
         %if  noise signal
       E_th(1)=p*energy_band(1) + (1-p)*E_th(1) ;
       E_th(2)=p*energy_band(2) + (1-p)*E_th(2) ;
       E_th(3)=p*energy_band(3) + (1-p)*E_th(3) ;
       E_th(4)=p*energy_band(4) + (1-p)*E_th(4) ;
   end
    
   
       
       
end

output=[];
for i = 1:divisions
    if (voice_flags(i) == 1)
        output = [output;ones(imax,1)];%whereever there is voice cascade 1's (like appending);so we can see where voice is there
    else
        output = [output;zeros(imax,1)];
    end
end
min_size = min(size(f), size(output));
output_mask =  output(1:min_size);%max value*wherever there is one; to amplify the signal which shows where voice present

% figure;plot(f,'b');
%  hold on;
%  plot(output_mask, 'r');
%  hold on;
% xlabel('lsed');

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

%  figure;plot(f,'b');
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






