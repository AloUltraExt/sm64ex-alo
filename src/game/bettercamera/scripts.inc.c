static void newcam_angle_rotate(void)
{
    newcam_yaw += 0x100;
    print_text(32,32,"hi i am a script");
    print_text_fmt_int(32,48,"%d",newcam_yaw);
}
