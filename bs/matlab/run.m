function run(input_file, runs)
    fprintf('[%s] Loading ...\n', input_file);
    tic;
    data = readtable(input_file, 'Delimiter', ' ', 'ReadVariableNames', false);
    % fetch columns of the input table, data
    sptprice   = table2array(data(:,1));
    strike     = table2array(data(:,2));
    rate       = table2array(data(:,3));
    divq       = table2array(data(:,4));
    volatility = table2array(data(:,5));
    time       = table2array(data(:,6));
    optiontype = string(table2array(data(:,7))) == 'P'; % convert cells to strings
    divs       = table2array(data(:,8));
    dgrefval   = table2array(data(:,9));
    load_time = toc;
    fprintf('[%s] Loaded in %.2f s\n', input_file, load_time);
    elapsed = zeros(1, runs);
    for id = 1:runs
        tic;
        OptionPrice = BlkSchls(sptprice,strike,rate,volatility,time,optiontype);
        elapsed(id) = toc;
    end
    fprintf('[%s] The average elapsed time with %d runs (ms): %.3f\n', input_file, runs, mean(elapsed)*1000);
    disp(elapsed);
    disp('Verify top 10 option prices');
    disp(OptionPrice(1:10));
end

% Read file
% https://www.mathworks.com/help/matlab/ref/readtable.html
