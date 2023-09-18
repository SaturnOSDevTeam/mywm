#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

Display* dpy;
Window root;

void set_background() {
    pid_t pid = fork();
    if (pid == 0) {
        char* feh_args[] = {"feh", "--bg-fill", "~/wywm/background.jpg", NULL};
        execvp("feh", feh_args);
        exit(0);
    }
}

void handle_events() {
    XEvent ev;
    XNextEvent(dpy, &ev);

    // Handle different types of X events
    switch (ev.type) {
        case FocusIn:
            // Implement focus handling logic
            break;
        case FocusOut:
            // Implement focus handling logic
            break;
        case KeyPress:
            // Handle key press events
            {
                KeySym key = XLookupKeysym(&ev.xkey, 0);

                // Example: Open Nemo on Ctrl + N
                if (ev.xkey.state & ControlMask && key == XK_n) {
                    system("nemo &");
                }

                // Example: Open Firefox on Ctrl + F
                else if (ev.xkey.state & ControlMask && key == XK_f) {
                    system("firefox &");
                }

                                // Example: Open Firefox on Ctrl + A
                else if (ev.xkey.state & ControlMask && key == XK_a) {
                    system("alacritty &");
                }

                // Example: Close active window on Alt + F4
                else if (ev.xkey.state & Mod1Mask && key == XK_F4) {
                    Window focusedWindow;
                    int revert;
                    XGetInputFocus(dpy, &focusedWindow, &revert);

                    Atom wmDeleteWin = XInternAtom(dpy, "WM_DELETE_WINDOW", True);
                    XEvent deleteEvent;
                    deleteEvent.type = ClientMessage;
                    deleteEvent.xclient.window = focusedWindow;
                    deleteEvent.xclient.message_type = wmDeleteWin;
                    deleteEvent.xclient.format = 32;
                    deleteEvent.xclient.data.l[0] = wmDeleteWin;
                    deleteEvent.xclient.data.l[1] = CurrentTime;

                    XSendEvent(dpy, focusedWindow, False, NoEventMask, &deleteEvent);
                }

                // Add more key bindings as needed
            }
            break;
        case CreateNotify:
            // Implement window creation handling logic
            break;
        case DestroyNotify:
            // Implement window destruction handling logic
            break;
        // Add more event types as needed
        default:
            break;
    }
}

void handle_signal(int sig) {
    if (sig == SIGINT || sig == SIGTERM) {
        // Clean up and close the display
        XCloseDisplay(dpy);
        exit(0);
    }
}

int main() {
    // Open the display and get the root window
    dpy = XOpenDisplay(NULL);
    root = DefaultRootWindow(dpy);

    // Set up event mask for the root window
    XSelectInput(dpy, root, SubstructureNotifyMask | KeyPressMask | FocusChangeMask);

    // Set background image using feh
    set_background();

    // Register signal handlers for graceful termination
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    // Enable window manager delete protocol
    Atom wmDeleteWin = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(dpy, root, &wmDeleteWin, 1);

    // Event loop
    while (1) {
        handle_events();
    }

    return 0;
}
