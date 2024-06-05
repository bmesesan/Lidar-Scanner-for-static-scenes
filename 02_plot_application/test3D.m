%investigate 3D plotting
clear
clc
close all

format long;
load file3.txt;

stepper_angle_constant = 87890625e-09;
disp(num2str(stepper_angle_constant,'%.9f'));
stepper_steps = 4096;
max_angle_x = stepper_steps * stepper_angle_constant;
stepper_resolution = 8;
measurements_x = stepper_steps / stepper_resolution + 1;
measurements_y = 121;
increment = stepper_angle_constant * stepper_resolution;

theta = 0:-1:-120;
phi = 0:increment:max_angle_x;
r = file3(:,:);

x = ones(measurements_y, measurements_x);
x = x.*(-1000);
y = ones(measurements_y, measurements_x);
y = y.*(-1000);
z = ones(measurements_y, measurements_x);
z = z.*(-1000);

figure;
hold on;
for i = 1:measurements_y
    for j = 1:measurements_x
        if r(i,j) ~= 1
            if r(i,j) <= 1000
                x(i, j) = r(i,j) * sin(deg2rad(theta(i))) * cos(deg2rad(phi(j)));
                y(i, j) = r(i,j) * sin(deg2rad(theta(i))) * sin(deg2rad(phi(j)));
                z(i, j) = r(i,j) * cos(deg2rad(theta(i)));
            end
        end
    end
end

plot3(x, y, z, 'mo', 'MarkerSize', 1);
xlabel('x');
ylabel('y');
zlabel('z');
xlim([-200, 200]);
ylim([-200, 200]);
zlim([-200, 200]);