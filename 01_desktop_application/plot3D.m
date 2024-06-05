%investigate 3D plotting
clear
clc
close all

format long;
load results.txt;
r = results(:,:);

load params.txt;
parameters = params(:,:);

stepper_angle_constant = 87890625e-09;
disp(num2str(stepper_angle_constant,'%.9f'));

stepper_resolution = (parameters(1));
stepper_max_steps = (parameters(2));
servo_resolution = (parameters(3));
servo_max_angle = (parameters(4));
servo_start_position = (parameters(5));

max_angle_x = stepper_max_steps * stepper_angle_constant;
measurements_x = stepper_max_steps / stepper_resolution + 1;

measurements_y = floor((servo_start_position - servo_max_angle) / servo_resolution) + 1;
increment_phi = stepper_angle_constant * stepper_resolution;

theta = servo_start_position:(-servo_resolution):servo_max_angle;
phi = 0:increment_phi:max_angle_x;

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
xlim([-300, 300]);
ylim([-300, 300]);
zlim([-300, 300]);