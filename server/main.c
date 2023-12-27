/*
 * File:   main.c
 * Author: Mantra
 * Program : MFS100 C Sample Program
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "./MFS100V11.h"
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int FingerTemplateLength = 2000;
struct timeval tv;
long *device = NULL;
void PrintErrorMsg(int errorno);
int getkey();

int getkey()
{
    struct termios oldt,
        newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int Img_Write_to_file(unsigned char *frame, char *file, int ht, int wd)
{

    char dir_path[100] = "./images/";

    strcat(dir_path, file);

    printf("PATH:%s\n", dir_path);

    void *device = NULL;
    FILE *ofile;
    ofile = fopen(dir_path, "wb");
    if (ofile == NULL)
    {
        printf("PROBELM OPENING PATH: %s \n", dir_path);
    }
    unsigned char *Imagedata;
    int ImageSize = (ht * wd) + 1078;
    Imagedata = (unsigned char *)malloc(ImageSize);
    int ret = MFS100ConvertRawToBmp(device, frame, Imagedata, ht, wd);
    printf("image len from MFS100ConvertRawToBmp is = %d\n", ret);
    fwrite(Imagedata, 1, ImageSize, ofile);
    fclose(ofile);
    free(Imagedata);

    return 1;
}

int Write_Template_ISO_ANSI(unsigned char *Template, char *fileout, int TemplateSize)
{

    char dir_path[100] = "./templates/";

    strcat(dir_path, fileout);

    FILE *ofile;
    ofile = fopen(dir_path, "wb");
    fwrite(Template, 1, TemplateSize, ofile);
    printf("WRITING TEMPLATE OF SIZE:%d", TemplateSize);
    fclose(ofile);
    return 1;
}

void Read_Template_ISO_ANSI(char *templateFile, char *filein, int *template_length)
{
    // This function reads the ISO template from File stored locally on FS

    char dir_path[100] = "./templates/";

    strcat(dir_path, filein);

    FILE *ptr;
    char ch;
    ptr = fopen(dir_path, "rb");

    int i = 0;

    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }

    printf("content of this file are \n");

    while (!feof(ptr))
    {
        ch = fgetc(ptr);
        // printf("%c", ch);
        templateFile[i++] = ch;
    }

    *template_length = i - 1;

    fclose(ptr);
}

// void CompareTwoFingerTemplates()
// {

//     int ret = 0;
//     int score = 0;

//     unsigned char *Iso_19794_2_Template1;
//     Iso_19794_2_Template1 = (unsigned char *)malloc(FingerTemplateLength);
//     unsigned char *Iso_19794_2_Template2;
//     Iso_19794_2_Template2 = (unsigned char *)malloc(FingerTemplateLength);
//     int ISOTemplateLength1 = 0;
//     int ISOTemplateLength2 = 0;

//     Read_Template_ISO_ANSI(Iso_19794_2_Template1, "1234567_iso_template.fmr", &ISOTemplateLength1);

//     Read_Template_ISO_ANSI(Iso_19794_2_Template2, "1234567_iso_template.fmr", &ISOTemplateLength2);

//     ret = MFS100MatchISO(device, Iso_19794_2_Template1, Iso_19794_2_Template2, 180, &score);

//     if (ret != 0)
//         PrintErrorMsg(ret);
//     if (score > 9600)
//     {
//         printf("Custom ISO template matches with score :%d\n", (int)score);
//     }
// }

void PrintErrorMsg(int errorno)
{
    switch (errorno)
    {

    case MFS100_E_NOT_GOOD_IMAGE:
        printf("Input Image is not Good\n");
        break;
    case MFS100_E_NO_DEVICE:
        printf("MFS100 not Found\n");
        break;
    case MFS100_E_NOT_INITIALIZED:
        printf("MFS100 not initialized\n");
        break;
    case MFS100_E_CORRUPT_SERIAL:
        printf("Serial no is corrupted\n");
        break;
    case MFS100_E_INVALIDPARAM:
        printf("Invalid Function parameter\n");
        break;
    case MFS100_E_LATENT_FINGER:
        printf("Latent Finger on device, clean and then initialize\n");
        break;
    case MFS100_E_LOAD_FIRMWARE_FAILED:
        printf("Firmware cannot load on device, try again or check security setting at udev\n");
        break;
    case MFS100_E_BLANKIMAGE:
        printf("Invalid image or unsupported image format\n");
        break;
    case MFS100_E_MEMORY:
        printf("Memory allocation failed\n");
        break;
    case MFS100_E_OTHER:
        printf("Other unspecified Error\n");
        break;
    case MFS100_E_NOT_IMPLEMENTED:
        printf("Function Not Implemented\n");
        break;
    case MFS100_E_READ_ONLY:
        printf("value cannot be modified\n");
        break;
    case MFS100_E_NOT_DEFINED:
        printf("value is not defined\n");
        break;
    case MFS100_E_NULL_TEMPLATE:
        printf("template is null\n");
        break;
    case MFS100_E_USB_ERROR_IO:
        printf("IO Error\n");
        break;
    case MFS100_E_USB_ERROR_INVALID_PARAM:
        printf("Invalid parameters\n");
        break;
    case MFS100_E_USB_ERROR_ACCESS:
        printf("Cannot Access USB Port, Rights Problem\n");
        break;
    case MFS100_E_USB_ERROR_NO_DEVICE:
        printf("No device\n");
        break;
    case MFS100_E_USB_ERROR_NOT_FOUND:
        printf("Unknown Error\n");
        break;
    case MFS100_E_USB_ERROR_BUSY:
        printf("USB Port busy, try again\n");
        break;
    case MFS100_E_USB_ERROR_TIMEOUT:
        printf("USB Port Timeout \n");
        break;
    case MFS100_E_USB_ERROR_OVERFLOW:
        printf("USB data overflow\n");
        break;
    case MFS100_E_USB_ERROR_PIPE:
        printf("Cannot Access USB pipe\n");
        break;
    case MFS100_E_USB_ERROR_INTERRUPTED:
        printf("USB Hardware Inturrupt Error\n");
        break;
    case MFS100_E_USB_ERROR_NO_MEM:
        printf("USB No internal memory\n");
        break;
    case MFS100_E_USB_ERROR_NOT_SUPPORTED:
        printf("USB functionality not supported\n");
        break;
    case MFS100_E_USB_OPEN_FAILED:
        printf("USB port open failed\n");
        break;
    case MFS100_E_USB_CLAIM_INTERFACE_FAILED:
        printf("USB claim interface failed\n");
        break;
    case MFS100_E_USB_ERROR_OTHER:
        printf("USB related other error\n");
        break;
    case MFS100_E_SYNC_PROBLEM:
        printf("MFS100 Sync problem, try changing Xfer rate and check again\n");
        break;
    case MFS100_E_UNKNOWN_SENSOR:
        printf("Unknown Sensor\n");
        break;
    case MFS100_E_NULLPARAM:
        printf("Null Parameters\n");
        break;
    case MFS100_E_TIMEOUT:
        printf("Function Timeout\n");
        break;
    case MFS100_E_EXTRACTOR_INIT_FAILED:
        printf("Extractor Library cannot Initialize\n");
        break;
    case MFS100_E_FILE_IO:
        printf("Error occured while opening/reading file\n");
        break;
    case MFS100_E_BAD_LICENSE:
        printf("Provided license is not valid, or no license was found\n");
        break;
    case MFS100_E_BAD_FORMAT:
        printf("Unsupported Format\n");
        break;
    case MFS100_E_BAD_VALUE:
        printf("Invalid Value Provided\n");
        break;
    case MFS100_E_BAD_TEMPLATE:
        printf("Invalide template or unsupported template format\n");
        break;
    case MFS100_E_BAD_QUALITY:
        printf("Bad Quality Finger\n");
        break;
    case MFS100_E_CAPTURING_STOPPED:
        printf("Capturing stopped\n");
        break;
    }
}

int CaptureFrame(void *device, int width, int height, unsigned char *FinalFrame, unsigned char *bitmapdata, unsigned char *Iso_19794_2_Template, unsigned char *Ansi_378_2004_Template, int *ISOTemplateLength)
{
    unsigned char *PreviewFrame;
    PreviewFrame = (unsigned char *)malloc(width * height);
    // Start Capture
    int ret = MFS100StartXcan(device, 0, 0);
    if (ret)
    {
        PrintErrorMsg(ret);
        return ret;
    }
    int busy = 1;
    int Quality;

    int MIN_QUALITY_ALLOWED = 70;

    // MFS100RotateImage(device,180);
    while (busy == 1)
    {
        Quality = MFS100GetQuality(device);

        if (Quality < 0)
        {
            PrintErrorMsg(Quality);
            printf("MFS100 Stopped...\n");
            Quality = 0;
            goto cont;
        }

        ret = MFS100GetPreviewFrame(device, PreviewFrame);
        gettimeofday(&tv, NULL);
        printf("Quality = %d and time = %d,%d\n", Quality, (int)tv.tv_sec, (int)tv.tv_usec);
        if (Quality >= MIN_QUALITY_ALLOWED)
        {
        cont:
            if (Quality == MFS100_E_TIMEOUT)
            {
                printf("MFS100 Timeout from Capture, No Image captured..\n");
                Quality = 0;
            }
            busy = 0;
            ret = MFS100StopXcan(device);
            if (ret != 0)
            {
                printf("Stop xcan error\n");
                PrintErrorMsg(ret);
                return ret;
            }
        }
    }

    if (Quality < MIN_QUALITY_ALLOWED)
    {
        free(PreviewFrame);
        return MFS100_E_BAD_QUALITY;
    }

    ret = MFS100GetFinalFrame(device, FinalFrame);
    // Img_Write_to_file(FinalFrame,"Final_Frame.bmp",height,width);

    *ISOTemplateLength = FingerTemplateLength;
    ret = MFS100ExtractISOTemplate(device, FinalFrame, Iso_19794_2_Template, ISOTemplateLength);
    if (ret != 0)
        PrintErrorMsg(ret);

    // Extract ANSI Template
    int ANSITemplateLength = FingerTemplateLength;
    ret = MFS100ExtractANSITemplate(device, FinalFrame, Ansi_378_2004_Template, &ANSITemplateLength);
    if (ret != 0)
        PrintErrorMsg(ret);

    free(PreviewFrame);
    return 0;
}

int CaptureAndMatch(void *device)
{
    long width = MFS100GetWidth(device);
    long height = MFS100GetHeight(device);
    int ret = 0;

    int score = 0;

    unsigned char *FinalFrame1;
    unsigned char *FinalFrame2;
    unsigned char *BitmapData1;
    unsigned char *BitmapData2;
    FinalFrame1 = (unsigned char *)malloc(width * height);
    FinalFrame2 = (unsigned char *)malloc(width * height);
    BitmapData1 = (unsigned char *)malloc((width * height) + 1078);
    BitmapData2 = (unsigned char *)malloc((width * height) + 1078);

    unsigned char *Iso_19794_2_Template1;
    Iso_19794_2_Template1 = (unsigned char *)malloc(FingerTemplateLength);

    unsigned char *Iso_19794_2_Template2;
    Iso_19794_2_Template2 = (unsigned char *)malloc(FingerTemplateLength);

    unsigned char *Ansi_378_2004_Template1;
    Ansi_378_2004_Template1 = (unsigned char *)malloc(FingerTemplateLength);

    unsigned char *Ansi_378_2004_Template2;
    Ansi_378_2004_Template2 = (unsigned char *)malloc(FingerTemplateLength);

    int ISOTemplateLength1 = 0;
    int ISOTemplateLength2 = 0;

    char roll_number[40];

    printf("Enter the Roll Number\n");

    // Reads n-1 ie 7 characters (8-1=7)
    fgets(roll_number, 8, stdin);

    printf("Place finger and press any key and enter to capture first frame\n");
    getkey();

repeat:

    printf("Place finger and press enter to capture first frame\n");
    ret = CaptureFrame(device, width, height, FinalFrame1, BitmapData1, Iso_19794_2_Template1, Ansi_378_2004_Template1, &ISOTemplateLength1);
    if (ret != 0)
    {
        PrintErrorMsg(ret);
        goto err;
    }

    // Write Image to File
    Img_Write_to_file(FinalFrame1, strcat(roll_number, "_Frame1.bmp"), height, width);
    //    Write_Template_ISO_ANSI(Iso_19794_2_Template1,"ISO_19794_2_Template1.fmr",ISOTemplateLength1);
    printf("Bitmap Image and ISO Template ISO_19794_1_Template.iso of First Frame saved to current path..\n");

    printf("Place finger and press any key and enter to capture second frame\n");
    getkey();
    ret = CaptureFrame(device, width, height, FinalFrame2, BitmapData2, Iso_19794_2_Template2, Ansi_378_2004_Template2, &ISOTemplateLength2);
    if (ret != 0)
    {
        PrintErrorMsg(ret);

        goto err;
    }

    // TRUNCATE THE TRAILING PART IN ROLL NUMBER STRING

    roll_number[7] = '\0';

    // Write Image to File
    Img_Write_to_file(FinalFrame2, strcat(roll_number, "_Frame2.bmp"), height, width);

    printf("Bitmap Image and ISO Template ISO_19794_2_Template.iso of Second Frame saved to current path..\n");

    // TRUNCATE THE TRAILING PART IN ROLL NUMBER STRING

    roll_number[7] = '\0';

    // Match ISO Templates

    ret = MFS100MatchISO(device, Iso_19794_2_Template1, Iso_19794_2_Template2, 180, &score);
    if (ret != 0)
        PrintErrorMsg(ret);
    if (score > 9600)
    {

        Write_Template_ISO_ANSI(Iso_19794_2_Template2, strcat(roll_number, "_iso_template.fmr"), ISOTemplateLength2);

        // CORRECT THE ROLL NUMBER STRING

        roll_number[7] = '\0';
    }
    else
        printf("ISO template Not matches, score :%d\n", (int)score);

    // Match ANSI Templates
    ret = MFS100MatchANSI(device, Ansi_378_2004_Template1, Ansi_378_2004_Template2, 180, &score);
    if (ret != 0)
        PrintErrorMsg(ret);
    if (score > 9600)
    {
        printf("ANSI template matches with score :%d\n", (int)score);
    }
    else
        printf("ANSI template Not matches, score :%d\n", (int)score);

    printf("Press Enter to capture frame again, or any other key to exit\n");
    if (getkey() == 10)
        goto repeat;

err:
    free(FinalFrame1);
    free(FinalFrame2);
    free(BitmapData1);
    free(BitmapData2);
    free(Iso_19794_2_Template1);
    free(Iso_19794_2_Template2);
    free(Ansi_378_2004_Template1);
    free(Ansi_378_2004_Template2);
    return 0;
}

////void (*MFS100AutoCaptureCallBack)(unsigned char*)
// void MFS100AutoCaptureCallBack2(unsigned char* Frame)
//{
//     printf("callback fired\n");
// }

void MFS100AutoCaptureCallBack2(unsigned char *Frame)
{
    printf("callback fired test 1\n");
    long width = MFS100GetWidth(NULL);
    long height = MFS100GetHeight(NULL);
    // Img_Write(Frame,"test.bmp",height,width);
    Img_Write_to_file(Frame, "test_callback.bmp", height, width);
}

int AutoCaptureAndMatch(void *device)
{
    long width = MFS100GetWidth(device);
    long height = MFS100GetHeight(device);
    int ret = 0;
    int score = 0;

    unsigned char *FinalFrame1;
    unsigned char *FinalFrame2;
    unsigned char *BitmapData1;
    unsigned char *BitmapData2;
    FinalFrame1 = (unsigned char *)malloc(width * height);
    FinalFrame2 = (unsigned char *)malloc(width * height);
    BitmapData1 = (unsigned char *)malloc((width * height) + 1078);
    BitmapData2 = (unsigned char *)malloc((width * height) + 1078);

    unsigned char *Iso_19794_2_Template1;
    Iso_19794_2_Template1 = (unsigned char *)malloc(FingerTemplateLength);

    unsigned char *Iso_19794_2_Template2;
    Iso_19794_2_Template2 = (unsigned char *)malloc(FingerTemplateLength);

    unsigned char *Ansi_378_2004_Template1;
    Ansi_378_2004_Template1 = (unsigned char *)malloc(FingerTemplateLength);

    unsigned char *Ansi_378_2004_Template2;
    Ansi_378_2004_Template2 = (unsigned char *)malloc(FingerTemplateLength);

    int ISOTemplateLength1 = 0;
    int ISOTemplateLength2 = 0;
    int ANSITemplateLength1 = 0;
    int ANSITemplateLength2 = 0;
    int Quality1 = 0;
    int Quality2 = 0;
    int NFIQ1 = 0;
    int NFIQ2 = 0;

    printf("Place finger and press any key and enter to capture first frame\n");
    getkey();

repeat:
    printf("Place finger and press enter to capture first frame\n");
    ret = MFS100AutoCapture(device, 10000, 60, FinalFrame1, BitmapData1, Iso_19794_2_Template1, &ISOTemplateLength1, Ansi_378_2004_Template1, &ANSITemplateLength1, &Quality1, &NFIQ1, MFS100AutoCaptureCallBack2);
    if (ret != 0)
    {
        PrintErrorMsg(ret);
        goto err;
    }

    // Write Image to File
    Img_Write_to_file(FinalFrame1, "Frame1.bmp", height, width);
    Write_Template_ISO_ANSI(Iso_19794_2_Template1, "ISO_19794_2_Template1.fmr", ISOTemplateLength1);
    printf("Bitmap Image and ISO Template ISO_19794_1_Template.iso of First Frame saved to current path..\n");

    printf("Place finger and press any key and enter to capture second frame\n");
    getkey();
    ret = MFS100AutoCapture(device, 10000, 60, FinalFrame2, BitmapData2, Iso_19794_2_Template2, &ISOTemplateLength2, Ansi_378_2004_Template2, &ANSITemplateLength2, &Quality2, &NFIQ2, MFS100AutoCaptureCallBack2);
    if (ret != 0)
    {
        PrintErrorMsg(ret);
        goto err;
    }
    // Write Image to File
    Img_Write_to_file(FinalFrame2, "Frame2.bmp", height, width);
    Write_Template_ISO_ANSI(Iso_19794_2_Template2, "ISO_19794_2_Template2.fmr", ISOTemplateLength2);
    printf("Bitmap Image and ISO Template ISO_19794_2_Template.iso of Second Frame saved to current path..\n");

    // Match ISO Templates

    ret = MFS100MatchISO(device, Iso_19794_2_Template1, Iso_19794_2_Template2, 180, &score);
    if (ret != 0)
        PrintErrorMsg(ret);
    if (score > 9600)
        printf("ISO template matches with score :%d\n", (int)score);
    else
        printf("ISO template Not matches, score :%d\n", (int)score);

    // Match ANSI Templates
    ret = MFS100MatchANSI(device, Ansi_378_2004_Template1, Ansi_378_2004_Template2, 180, &score);
    if (ret != 0)
        PrintErrorMsg(ret);
    if (score > 9600)
        printf("ANSI template matches with score :%d\n", (int)score);
    else
        printf("ANSI template Not matches, score :%d\n", (int)score);

    printf("Press Enter to capture frame again, or any other key to exit\n");

    if (getkey() == 10)
        goto repeat;

err:
    free(FinalFrame1);
    free(FinalFrame2);
    free(BitmapData1);
    free(BitmapData2);
    free(Iso_19794_2_Template1);
    free(Iso_19794_2_Template2);
    free(Ansi_378_2004_Template1);
    free(Ansi_378_2004_Template2);
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    return 0;
}

void IdentifyFromTemplates()
{
    // 1. Capture Finger Impression through scanner
    long width = MFS100GetWidth(device);
    long height = MFS100GetHeight(device);
    int ret = 0;

    int score = 0;

    // Max score initialized to threshold
    int max_score = 9600;

    // flag to check if scanned matched any
    int Matched = 0;

    unsigned char *FinalFrame1;
    unsigned char *FinalFrame2;
    unsigned char *BitmapData1;
    unsigned char *BitmapData2;
    FinalFrame1 = (unsigned char *)malloc(width * height);
    FinalFrame2 = (unsigned char *)malloc(width * height);
    BitmapData1 = (unsigned char *)malloc((width * height) + 1078);
    BitmapData2 = (unsigned char *)malloc((width * height) + 1078);

    unsigned char *Iso_19794_2_Template1;
    Iso_19794_2_Template1 = (unsigned char *)malloc(FingerTemplateLength);

    unsigned char *Iso_19794_2_Template2;
    Iso_19794_2_Template2 = (unsigned char *)malloc(FingerTemplateLength);

    unsigned char *Ansi_378_2004_Template1;
    Ansi_378_2004_Template1 = (unsigned char *)malloc(FingerTemplateLength);

    unsigned char *Ansi_378_2004_Template2;
    Ansi_378_2004_Template2 = (unsigned char *)malloc(FingerTemplateLength);

    int ISOTemplateLength1 = 0;
    int ISOTemplateLength2 = 0;

    printf("\nPlace finger and press any key and enter to capture first frame\n");
    getkey();

    printf("\nPlace finger and press enter to capture first frame\n");
    ret = CaptureFrame(device, width, height, FinalFrame1, BitmapData1, Iso_19794_2_Template1, Ansi_378_2004_Template1, &ISOTemplateLength1);
    if (ret != 0)
    {
        PrintErrorMsg(ret);
        goto err;
    }

    // At this point we have the impression

    // 2. list through all the templates

    char *filename = (char *)malloc(255);
    char *matched_template = (char *)malloc(255);

    DIR *d;
    struct dirent *dir;
    d = opendir("./templates/");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {

            // 3. Template name is stored in d_name

            // Read template from file

            strcpy(filename, dir->d_name);

            // If filepath is . or .. do nothing for such filenames

            if (strcmp(filename, ".") && strcmp(filename, ".."))

            {
                printf("Reading Template INSIDE LOOP: %s \n", filename);

                Read_Template_ISO_ANSI(Iso_19794_2_Template2, filename, &ISOTemplateLength2);

                // // Now Template 2 stores content of template read from FS

                // // 4. Get score reading

                ret = MFS100MatchISO(device, Iso_19794_2_Template1, Iso_19794_2_Template2, 180, &score);

                if (ret != 0)
                    PrintErrorMsg(ret);

                printf("Score Obtained: %d\n", (int)score);

                if (score >= max_score)
                {
                    // Fingerprints are matching over threshold
                    max_score = score;
                    Matched = 1;
                    strcpy(matched_template, filename);
                }

                // RESET filename buffer

                strcpy(filename, "");

                // RESET IsoTemplate2 Buffer
                strcpy(Iso_19794_2_Template2, "");
            }
        }
        closedir(d);
    }

    else
    {
        printf("Directory doesnt exist");
    }

    // If Matched means we had a match

    if (Matched)
    {
        printf("\n\nFingerprint Matched with template: %s with score of %d\n", matched_template, max_score);
    }

err:
    free(FinalFrame1);
    free(FinalFrame2);
    free(BitmapData1);
    free(BitmapData2);
    free(Iso_19794_2_Template1);
    free(Iso_19794_2_Template2);
    free(Ansi_378_2004_Template1);
    free(Ansi_378_2004_Template2);
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("\n\nNo argument passed through command line!");
    }
    else
    {
        printf("\nArgument supplied: ");
        for (int i = 1; i < argc; i++)
        {
            printf("%s\t", argv[i]);
        }
    }

    // Based on argument passed to process we perform certain actions

    /*

        ENROLL FINGER

        schema: 2 args - 1: ENROLL 2:name of user

        IDENTIFY USER

        schema: 1 args 1: IDENTIFY


    */

    int ret = 0;
    int ch = 0;
    int version = MFS100GetSDKVersion();
    printf("MFS100 Library Version %d loaded\n", version);

    char Make[10];
    char Model[10];
    ret = MFS100GetInfo(Make, Model);
    if (ret != 0)
        PrintErrorMsg(ret);
    else
        printf("Make = %s, Model = %s\n", Make, Model);

    unsigned char *serialno = (unsigned char *)calloc(11, sizeof(unsigned char));

    // For High speed you can try with Xfer_Size of 131072,16384,512
    // For Full speed you can try with Xfer_Size of 64,16384,15360,131072
    // You can pass 30 to 150 for latent threshold, lesser the value, software will be more sensitive against latent detection
    // if pcbversion is 4.1 then pass 41 as last parameter else pass 0
    // device = (long*)MFS100Init(serialno,60,16384,31);

    device = (long *)MFS100Init(serialno, 60, 16384, 31);

    ret = MFS100LastErrorCode();
    if (ret != 0)
    {
        if (ret != 0)
            PrintErrorMsg(ret);
        goto err;
    }

    if (!device)
    {
        printf("Device Not Connected\n");
        goto err;
    }

    printf("Init Success....Serial No = %s\n", serialno);

    ret = MFS100DeviceConnected();
    if (ret != 0)
    {
        if (ret != 0)
            PrintErrorMsg(ret);
        goto err;
    }

    printf("ARG:%s", argv[1]);

    if (!strcmp(argv[1], "ENROLL"))
    {
        CaptureAndMatch(device);
    }

err:
    free(serialno);
    ret = MFS100Uninit(device);
    if (ret != 0)
        PrintErrorMsg(ret);
    if (ret == 0)
        printf("Device Closed Successfully from Main\n");
    return ret;
}
