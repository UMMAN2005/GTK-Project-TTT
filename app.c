#include "app.h"
#include <stdio.h>

GtkWidget*** buttons;
int N, M;
int currentPlayer = 1;
GtkApplication* app;
int restartCount = 0;

void buttonClicked(GtkWidget* widget, gpointer data) {
    int row = GPOINTER_TO_INT(data) / M;
    int col = GPOINTER_TO_INT(data) % M;

    if (gtk_button_get_label(GTK_BUTTON(widget)) == NULL) {
        if (restartCount) {
            restartCount = 0;
            currentPlayer = 1;
        }
        if (currentPlayer == 1) {
            gtk_button_set_label(GTK_BUTTON(widget), "X");
            if (checkWin(1, row, col)) {
                showResultDialog("Player 1 (X) wins!");
            } else if (checkDraw()) {
                showResultDialog("Draw!\n");
            }
            currentPlayer = 2;
        } else {
            gtk_button_set_label(GTK_BUTTON(widget), "O");
            if (checkWin(2, row, col)) {
                showResultDialog("Player 2 (O) wins!\n");
            } else if (checkDraw()) {
                showResultDialog("Draw!\n");
            }
            currentPlayer = 1;
        }
    }
}

void activate(GtkApplication* app, gpointer userData) {
    GtkWidget* window;
    GtkWidget* grid;

    printf("Enter the board length (N): ");
    scanf("%d", &N);
    printf("Enter the board width (M): ");
    scanf("%d", &M);

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Tic-Tac-Toe");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    buttons = (GtkWidget***)malloc(N * sizeof(GtkWidget**));
    for (int i = 0; i < N; i++) {
        buttons[i] = (GtkWidget**)malloc(M * sizeof(GtkWidget*));
        for (int j = 0; j < M; j++) {
            buttons[i][j] = gtk_button_new_with_label(NULL);
            gtk_widget_set_size_request(buttons[i][j], 100, 100);
            gtk_widget_set_name(buttons[i][j], "button");
            setColor(buttons, NULL);
            g_signal_connect(buttons[i][j], "clicked", G_CALLBACK(buttonClicked), GINT_TO_POINTER(i * M + j));
            gtk_grid_attach(GTK_GRID(grid), buttons[i][j], i, j, 1, 1);
        }
    }

    gtk_widget_show_all(window);
}

bool checkWin(int player, int row, int col) {
    gchar playerSymbol = (player == 1) ? 'X' : 'O';

    int horizontalCount = 0;
    int verticalCount = 0;
    int diagonalCount1 = 0;
    int diagonalCount2 = 0;

    // Check horizontally
    for (int i = 0; i < M; i++) {
        GtkWidget* button = buttons[row][i];
        const gchar* labelText = gtk_button_get_label(GTK_BUTTON(button));
        if (labelText != NULL && labelText[0] == playerSymbol) {
            horizontalCount++;
            if (horizontalCount == 3) {
                return true;
            }
        } else {
            horizontalCount = 0;
        }
    }

    // Check vertically
    for (int i = 0; i < N; i++) {
        GtkWidget* button = buttons[i][col];
        const gchar* labelText = gtk_button_get_label(GTK_BUTTON(button));
        if (labelText != NULL && labelText[0] == playerSymbol) {
            verticalCount++;
            if (verticalCount == 3) {
                return true;
            }
        } else {
            verticalCount = 0;
        }
    }

    // Check diagonals
    for (int i = -2; i <= 2; i++) {
        int r1 = row + i;
        int c1 = col + i;
        int r2 = row - i;
        int c2 = col + i;

        if (r1 >= 0 && r1 < N && c1 >= 0 && c1 < M) {
            GtkWidget* button1 = buttons[r1][c1];
            const gchar* labelText1 = gtk_button_get_label(GTK_BUTTON(button1));
            if (labelText1 != NULL && labelText1[0] == playerSymbol) {
                diagonalCount1++;
                if (diagonalCount1 == 3) {
                    return true;
                }
            } else {
                diagonalCount1 = 0;
            }
        }

        if (r2 >= 0 && r2 < N && c2 >= 0 && c2 < M) {
            GtkWidget* button2 = buttons[r2][c2];
            const gchar* labelText2 = gtk_button_get_label(GTK_BUTTON(button2));
            if (labelText2 != NULL && labelText2[0] == playerSymbol) {
                diagonalCount2++;
                if (diagonalCount2 == 3) {
                    return true;
                }
            } else {
                diagonalCount2 = 0;
            }
        }
    }

    return false;
}

bool checkDraw() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            const gchar* labelText = gtk_button_get_label(GTK_BUTTON(buttons[i][j]));
            if (labelText == NULL) {
                return false;
            }
        }
    }
    return true;
}

void showResultDialog(const char* message) {
    GtkWidget* dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, message);
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "Choose an option:");

    gtk_dialog_add_button(GTK_DIALOG(dialog), "Restart", 1);
    gtk_dialog_add_button(GTK_DIALOG(dialog), "Quit", 2);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    int result = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    if (result == 1) {
        restartGame();
        currentPlayer = 1;
    } else if (result == 2) {
        quitApplication();
    }
}

void restartGame() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            GtkWidget* button = GTK_WIDGET(buttons[i][j]);
            gtk_button_set_label(GTK_BUTTON(button), "");
            gtk_button_set_label(GTK_BUTTON(button), NULL);
            gtk_widget_set_name(buttons[i][j], "button");
        }
    }
    setColor(buttons, NULL);
    restartCount = 1;
    currentPlayer = 1;
}

void quitApplication() {
    g_application_quit(G_APPLICATION(app));
}

void setColor(GtkWidget*** widgets, gpointer userData) {
    GtkCssProvider* cssProvider = gtk_css_provider_new();
    GError* error = NULL;

    if (!gtk_css_provider_load_from_path(cssProvider, "tictactoe_style.css", &error)) {
        g_error("Error loading CSS file: %s", error->message);
        g_clear_error(&error);
    }

    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void cleanup() {
    for (int i = 0; i < N; i++) {
        free(buttons[i]);
    }
    free(buttons);
}