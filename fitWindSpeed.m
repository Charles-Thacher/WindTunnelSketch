function [slope, intercept, eqnStr] = fitWindSpeed(pwmScales, windSpeeds)
% fitWindSpeed - Fits a linear model: windSpeed = slope * pwmScale + intercept
%
% Inputs:
%   pwmScales - Vector of 5 PWM scale values (0 to 255)
%   windSpeeds - Vector of 5 corresponding wind speeds
%
% Outputs:
%   slope - Slope of the best fit line
%   intercept - Intercept of the best fit line
%   eqnStr - String representation of the equation

    % Check that inputs are vectors of length 5
    if length(pwmScales) ~= 5 || length(windSpeeds) ~= 5
        error('Both inputs must be vectors of length 5.');
    end
    
    % Perform linear fit
    coeffs = polyfit(pwmScales, windSpeeds, 1); % degree 1 = linear fit
    slope = coeffs(1);
    intercept = coeffs(2);
    
    % Create a human-readable equation string
    % eqnStr = sprintf('Wind Speed = %.4f * PWM + %.4f', slope, intercept);

    disp("Slope: " + string(slope));
    disp("Intercept: " + string(intercept));
    fprintf('Equation: WindSpeed = %.4f * PWM + %.4f', slope, intercept);
    
    % Optional: plot data and fit
    figure;
    plot(pwmScales, windSpeeds, 'bo', 'MarkerSize', 8, 'DisplayName', 'Data Points');
    hold on;
    pwmFine = linspace(min(pwmScales), max(pwmScales), 100);
    windFine = polyval(coeffs, pwmFine);
    plot(pwmFine, windFine, 'r-', 'LineWidth', 2, 'DisplayName', 'Best Fit Line');
    xlim([0 255])
    ylim([0 round((windSpeeds(4)+3))])
    xlabel('PWM Scale (0-255)');
    ylabel('Wind Speed');
    title('Linear Fit of Wind Speed vs PWM');
    legend('show');
    grid on;
end
