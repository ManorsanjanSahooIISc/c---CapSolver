%% .................MOM FILLER........................................%%
function momMatrix = momFiller(node, patch, numPatch)

momMatrix = zeros(numPatch, numPatch);
for numSources = 1:numPatch
    %% .................Source patch edge calculation................ %%
    len1 = sqrt((node(patch(numSources,1),1) - node(patch(numSources,2),1))^2 + (node(patch(numSources,1),2) - node(patch(numSources,2),2))^2 + (node(patch(numSources,1),3) - node(patch(numSources,2),3))^2);
    len2 = sqrt((node(patch(numSources,1),1) - node(patch(numSources,3),1))^2 + (node(patch(numSources,1),2) - node(patch(numSources,3),2))^2 + (node(patch(numSources,1),3) - node(patch(numSources,3),3))^2);
    len3 = sqrt((node(patch(numSources,3),1) - node(patch(numSources,2),1))^2 + (node(patch(numSources,3),2) - node(patch(numSources,2),2))^2 + (node(patch(numSources,3),3) - node(patch(numSources,2),3))^2);
    maxlen = max(len1, len2);
    maxlen = max(maxlen, len3);
   
    %% ........................Area os source..........................%% 
  areas = computeArea(node(patch(numSources,1),:), node(patch(numSources,2),:), node(patch(numSources,3),:));
    
   %% .....................centroid of source.........................%%
    centroidSource(1,1) = (node(patch(numSources,1),1) + node(patch(numSources,2),1) + node(patch(numSources,3),1))/3;
    centroidSource(1,2) = (node(patch(numSources,1),2) + node(patch(numSources,2),2) + node(patch(numSources,3),2))/3;
    centroidSource(1,3) = (node(patch(numSources,1),3) + node(patch(numSources,2),3) + node(patch(numSources,3),3))/3;
   
    for numObserver = 1:numPatch
    %% ..............Observation patch centriod.....................%%
    centroidObserver(1,1) = (node(patch(numObserver,1),1) + node(patch(numObserver,2),1) + node(patch(numObserver,3),1))/3;
    centroidObserver(1,2) = (node(patch(numObserver,1),2) + node(patch(numObserver,2),2) + node(patch(numObserver,3),2))/3;
    centroidObserver(1,3) = (node(patch(numObserver,1),3) + node(patch(numObserver,2),3) + node(patch(numObserver,3),3))/3;
    distanceCenterToCenter = sqrt((centroidSource(1,1) - centroidObserver(1,1))^2 + (centroidSource(1,2) - centroidObserver(1,2))^2 + (centroidSource(1,3) - centroidObserver(1,3))^2);   
   
    %For Analytical Method....................%
        if (distanceCenterToCenter <= 10 * maxlen) %|| (rcent>10* maxlen)
        momEntry = analiticalIntegration( node( patch( numSources,1 ),: ), node( patch(numSources,2),:), node(patch(numSources,3),:), centroidObserver);       
    %For Seven Point............%
%           elseif (distanceCenterToCenter > 4 * maxlen) && (distanceCenterToCenter <= 10 * maxlen) 
%           momEntry = sevenPointRule(node(patch(numSources,1),:), node(patch(numSources,2),:), node(patch(numSources,3),:), centroidObserver) * areas;
           %For One Point..........................%
            else %if rcent>=10* maxlen
            momEntry = onePointRule(centroidObserver, centroidSource) * areas;
        end  
     momMatrix(numObserver, numSources) = momEntry;
%       MoM_entry = analiticalIntegration( node( patch( numSources,1 ),: ), node( patch(numSources,2),:), node(patch(numSources,3),:), centroidObserver);
%         momMatrix(numObserver, numSources) = MoM_entry;
    
    end
   % toc;
end
momMatrix = (1/(4*pi*8.854*1e-12)) * momMatrix;

%% .........................Elapsed time is 369.223295 seconds..........%%
