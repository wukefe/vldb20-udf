function OutputX = CNDF(InputX, invs2xPI)
    sign          = InputX < 0;
    xInput        = abs(InputX);
    expValues     = exp(-0.5 .* (InputX .* InputX));
    xNPrimeofX    = invs2xPI .* expValues;
    xK2           = 1.0 ./ (1.0 + 0.2316419 .* xInput);
    xK2_2         = xK2 .* xK2;
    xK2_3         = xK2 .* xK2_2;
    xK2_4         = xK2 .* xK2_3;
    xK2_5         = xK2 .* xK2_4;
    xLocal_1      = xK2 .* 0.319381530;
    xLocal_2      = (xK2_2 .* -0.356563782) + (xK2_3 .* 1.781477937) + (xK2_4 .* -1.821255978) + xK2_5 .* 1.330274429;
    xLocal        = 1.0 - xNPrimeofX .* (xLocal_2 + xLocal_1);
    OutputX       = (sign .* (1.0 - xLocal)) + (~sign) .* xLocal;
end

