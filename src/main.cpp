// C standard includes
#include <stdio.h>
#include <opencv2/opencv.hpp>
const auto M_PI = 3.14159265358979323846;

const int WIDTH = 1000;
const int HEIGHT = 1000;

int main()
{
    cv::Mat image = cv::Mat::zeros(cv::Size(WIDTH, HEIGHT), CV_64F);
    cv::Mat imageT_1 = cv::Mat::zeros(cv::Size(WIDTH, HEIGHT), CV_64F);

    // Number of nodes along axis x and y.
    auto Nx = WIDTH;
    auto Nz = HEIGHT;

    auto zMin = 0.0;
    auto zMax = 1.0;
    auto xMin = 0.0;
    auto xMax = 1.0;

    // Axis_z.
    cv::Mat Axis_z = cv::Mat::zeros(cv::Size(1, Nz), CV_64F);
    auto Delta_z = double((zMax - zMin) / (double(Nz - 1)));

    cv::Mat iz(1, Nz, CV_64F);

    for (int i = 0; i < Nz; i++)
    {
        iz.at<double>(0, i) = (double)i;
    }

    Axis_z = (iz - 1) * Delta_z;

    // Axis_x.
    cv::Mat Axis_x = cv::Mat::zeros(cv::Size(1, Nz), CV_64F);
    auto Delta_x = double((xMax - xMin) / (double(Nx - 1)));
    cv::Mat ix(1, Nz, CV_64F);

    for (int i = 0; i < Nx; i++)
    {
        ix.at<double>(0, i) = (double)i;
    }

    Axis_x = (ix - 1) * Delta_x;

    // Parameters of the analytical solution.
    auto k_z = 1.0;
    auto k_x = 2.0;
    auto Time = 0.02;
    // Create the initial values and final exact results.
    for (int iz = 0; iz < Nz; iz++)
    {
        for (int ix = 0; ix < Nx; ix++)
        {
            auto x = Axis_x.at<double>(0, ix);
            auto z = Axis_z.at<double>(0, iz);

            image.at<double>(iz, ix) = sin(k_x * M_PI * x) * sin(k_z * M_PI * z) + 1;
        }
    }

    cv::namedWindow("PDE solver", cv::WINDOW_AUTOSIZE);
    cv::startWindowThread();

    cv::Size frame_size(WIDTH, HEIGHT);
    int frames_per_second = 25;
    cv::VideoWriter videoWriter("video.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
                                frames_per_second, frame_size, true);

    double ht = 0.2;
    double hx = Delta_z;
    double kc = 1.0;
    double r = (ht * kc) / hx * hx;
    std::cout << "r=" << r << "\n";

    // calculate original min-max
    double original_min, original_max;
    cv::Point min_loc, max_loc;
    cv::minMaxLoc(image, &original_min, &original_max, &min_loc, &max_loc);

    for (int k = 0; k < 100000; k++)
    {
        if (k % 2000 == 0)
        {
            cv::Mat img_color;

            image.copyTo(img_color);
            img_color = (img_color / (original_max - original_min)) * 255.0;

            img_color.convertTo(img_color, CV_8UC1);

            cv::applyColorMap(img_color, img_color, cv::COLORMAP_JET);

            std::cout << image.at<double>(100, 100) << '\n';
            
            cv::Point min_loc, max_loc;
            double min, max;
            cv::minMaxLoc(image, &min, &max, &min_loc, &max_loc);
            
            std::cout << min << " " << max << "\n";
            
            cv::imshow("PDE solver", img_color);
            cv::waitKey(1);

            videoWriter.write(img_color);
        }
#pragma omp parallel for
        for (int i = 1; i < image.size().width - 1; i++)
        {
            for (int j = 1; j < image.size().height - 1; j++)
            {
                auto temp = r *
                            (image.at<double>(i, j + 1) +
                             image.at<double>(i + 1, j) +
                             image.at<double>(i, j - 1) +
                             image.at<double>(i - 1, j) - 4.0 * image.at<double>(i, j));

                imageT_1.at<double>(i, j) = image.at<double>(i, j) + temp;
            }
        }
        imageT_1.copyTo(image);
    }
    videoWriter.release();
    cv::imwrite("modified.png", image);
    return 0;
}