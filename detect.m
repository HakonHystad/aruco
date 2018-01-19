%% detect - main 
clear
% build: mexOpenCV track.cpp -L/usr/local/lib -lopencv_aruco -I/usr/local/include/opencv2 -I/usr/local/include/opencv -I/usr/local/include



cam = webcam;

h = imshow( snapshot(cam) );

% while true
    
    im = snapshot(cam);
    
    try
        trakced_im = track(im);
        set(h,'Cdata',tracked_im);
        drawnow;
    catch
%         break;
    end
    
% end% while true

clear cam;