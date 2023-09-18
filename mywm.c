#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

Display* dpy;
Window root;

void set_background() {
    pid_t pid = fork();
    if (pid == 0) {
        char *feh_args[] = {"feh", "--bg-fill", "/path/to/background.jpg", NULL};
        execvp("feh", feh_args);
        exit(0);
    }
}

void handle_events() {
    XEvent ev;

    // Ensure that the display is properly opened
    if (dpy == NULL) {
        fprintf(stderr, "Error: Failed to open display.\n");
        exit(1);
    }

    // Get the next event
    XNextEvent(dpy, &ev);

    // Handle different types of X events
    switch (ev.type) {
        // Handle the events
        // ...

        default:
            break;
    }
}

int main() {
    // Open the display and get the root window
    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
        fprintf(stderr, "Error: Failed to open display.\n");
        return 1;
    }
    root = DefaultRootWindow(dpy);

    // Set up event mask for the root window
    XSelectInput(dpy, root, SubstructureNotifyMask | KeyPressMask | FocusChangeMask);

    // Set background image using feh
    set_background();

    // Event loop
    while (1) {
        handle_events();
    }

    // Close the display
    XCloseDisplay(dpy);

    return 0;
}
