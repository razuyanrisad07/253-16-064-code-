#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants for limits
#define MAX_DISHES 100
#define MAX_ORDERS 200

#define MAX_NAME_LENGTH 50
#define MAX_DESC_LENGTH 100
#define MAX_ID_LENGTH 20
#define ADMIN_PASSWORD "admin123" // Set your desired admin password here

// Structure definitions
struct Dish
{
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESC_LENGTH];
    float price;
    int preparation_time; // in minutes
};

struct Order
{
    char id[10];
    char customer_name[50];
    char address[100];
    char contact_number[15];
    char dish_id[10];
    int status; // 1 for placed, 0 for canceled
};

// Global variables for counts
int dishCount = 0;
int orderCount = 0;

// Function prototypes
void loadData(struct Dish dishes[], struct Order orders[]);

void saveData(struct Dish dishes[], struct Order orders[]);

void addDish(struct Dish dishes[]);
void updateDish(struct Dish dishes[]);
void deleteDish(struct Dish dishes[]);
void viewAllDishes(struct Dish dishes[]);
void searchDishes(struct Dish dishes[]);
void viewSalesReport(struct Order orders[], struct Dish dishes[]);
void placeOrder(struct Order orders[], struct Dish dishes[]);
void cancelOrder(struct Order orders[]);
void viewAllOrders(struct Order orders[]);
void adminPanel(struct Dish dishes[], struct Order orders[]);
void customerPanel(struct Dish dishes[], struct Order orders[]);

// Main function
int main()
{
    struct Dish dishes[MAX_DISHES];
    struct Order orders[MAX_ORDERS];

    loadData(dishes, orders);

    int choice;
    while (1)
    {
        printf("\n=== Restaurant Management System ===\n");
        printf("1. Admin Panel\n");
        printf("2. Customer Panel\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            char password[20];
            printf("Enter admin password: ");
            scanf("%s", password);

            if (strcmp(password, ADMIN_PASSWORD) == 0)
            {
                adminPanel(dishes, orders);
            }
            else
            {
                printf("Incorrect password! Access denied.\n");
            }
            break;
        }
        case 2:
            customerPanel(dishes, orders);
            break;
        case 3:
            saveData(dishes, orders);
            printf("Exiting the application...\n");
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Admin panel function
void adminPanel(struct Dish dishes[], struct Order orders[])
{
    int choice;
    while (1)
    {
        printf("\n=== Admin Panel ===\n");
        printf("1. Add Dish\n");
        printf("2. Update Dish\n");
        printf("3. Delete Dish\n");
        printf("4. View All Dishes\n");
        printf("5. Search Dishes\n");
        printf("6. View Sales Report\n");
        printf("7. View All Orders\n");
        printf("8. Exit Admin Panel\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addDish(dishes);
            break;
        case 2:
            updateDish(dishes);
            break;
        case 3:
            deleteDish(dishes);
            break;
        case 4:
            viewAllDishes(dishes);
            break;
        case 5:
            searchDishes(dishes);
            break;
        case 6:
            viewSalesReport(orders, dishes);
            break;
        case 7:
            viewAllOrders(orders);
            break;
        case 8:
            return; // Exit the admin panel
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
}

// Customer panel function
void customerPanel(struct Dish dishes[], struct Order orders[])
{
    int choice;
    while (1)
    {
        printf("\n=== Customer Panel ===\n");
        printf("1. Place Order\n");
        printf("2. Cancel Order\n");
        printf("3. View All Dishes\n");
        printf("4. Exit Customer Panel\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            placeOrder(orders, dishes);
            break;
        case 2:
            cancelOrder(orders);
            break;
        case 3:
            viewAllDishes(dishes);
            break;
        case 4:
            return; // Exit the customer panel
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
}

// Load dishes and orders data from files
void loadData(struct Dish dishes[], struct Order orders[])
{
    FILE *dishFile = fopen("dishes.txt", "r");
    if (dishFile != NULL)
    {
        fread(&dishCount, sizeof(int), 1, dishFile);
        fread(dishes, sizeof(struct Dish), dishCount, dishFile);
        fclose(dishFile);
        printf("Loaded %d dishes from dishes.dat.\n", dishCount);
    }
    else
    {
        printf("Could not open dishes.dat for reading. Starting with an empty dish list.\n");
    }

    FILE *orderFile = fopen("orders.txt", "r");
    if (orderFile != NULL)
    {
        fread(&orderCount, sizeof(int), 1, orderFile);
        fread(orders, sizeof(struct Order), orderCount, orderFile);
        fclose(orderFile);
        printf("Loaded %d orders from orders.dat.\n", orderCount);
    }
    else
    {
        printf("Could not open orders.dat for reading. Starting with an empty order list.\n");
    }
}

// Save dishes and orders data into a file
void saveData(struct Dish dishes[], struct Order orders[])
{
    FILE *dishFile = fopen("dishes.txt", "w");
    if (dishFile != NULL)
    {
        fwrite(&dishCount, sizeof(int), 1, dishFile);
        fwrite(dishes, sizeof(struct Dish), dishCount, dishFile);
        fclose(dishFile);
        printf("Saved %d dishes to dishes.dat.\n", dishCount);
    }
    else
    {
        printf("Could not open dishes.dat for writing.\n");
    }

    FILE *orderFile = fopen("orders.txt", "w");
    if (orderFile != NULL)
    {
        fwrite(&orderCount, sizeof(int), 1, orderFile);
        fwrite(orders, sizeof(struct Order), orderCount, orderFile);
        fclose(orderFile);
        printf("Saved %d orders to orders.dat.\n", orderCount);
    }
    else
    {
        printf("Could not open orders.dat for writing.\n");
    }
}

// Function to add a new dish
void addDish(struct Dish dishes[])
{
    if (dishCount >= MAX_DISHES)
    {
        printf("Cannot add more dishes. Maximum limit reached (%d).\n", MAX_DISHES);
        return;
    }

    struct Dish newDish;

    printf("Enter dish ID: ");
    scanf("%s", newDish.id);
    printf("Enter dish name: ");
    scanf(" %[^\n]", newDish.name);
    printf("Enter dish description: ");
    scanf(" %[^\n]", newDish.description);
    printf("Enter dish price: ");
    scanf("%f", &newDish.price);
    printf("Enter preparation time (in minutes): ");
    scanf("%d", &newDish.preparation_time);

    dishes[dishCount] = newDish;
    dishCount++;

    printf("Dish '%s' added successfully!\n", newDish.name);
}

void cancelOrder(struct Order orders[])
{
    char id[10];
    printf("Enter order ID to cancel: ");
    scanf("%s", id);

    int orderFound = 0;
    for (int i = 0; i < orderCount; i++)
    {
        if (strcmp(orders[i].id, id) == 0)
        {
            orders[i].status = 0; // Set status to canceled
            printf("Order ID %s has been canceled successfully.\n", id);
            orderFound = 1;
            break;
        }
    }

    if (!orderFound)
    {
        printf("Order with ID %s not found.\n", id);
    }
}

void deleteDish(struct Dish dishes[])
{
    char id[10];
    printf("Enter dish ID to delete: ");
    scanf("%s", id);

    int dishFound = 0;
    for (int i = 0; i < dishCount; i++)
    {
        if (strcmp(dishes[i].id, id) == 0)
        {
            // Shift the remaining dishes left
            for (int j = i; j < dishCount - 1; j++)
            {
                dishes[j] = dishes[j + 1];
            }
            dishCount--; // Reduce the count of dishes
            printf("Dish ID %s has been deleted successfully.\n", id);
            dishFound = 1;
            break;
        }
    }

    if (!dishFound)
    {
        printf("Dish with ID %s not found.\n", id);
    }
}

void placeOrder(struct Order orders[], struct Dish dishes[])
{
    if (orderCount >= MAX_ORDERS)
    {
        printf("Cannot place more orders. Maximum limit reached (%d).\n", MAX_ORDERS);
        return;
    }

    struct Order newOrder;
    char dishId[10];
    int dishFound = 0;

    printf("Enter your name: ");
    scanf(" %[^\n]", newOrder.customer_name);
    printf("Enter your address: ");
    scanf(" %[^\n]", newOrder.address);
    printf("Enter your contact number: ");
    scanf("%s", newOrder.contact_number);

    printf("Enter dish ID to order: ");
    scanf("%s", dishId);

    // Check if the dish exists and is available
    for (int i = 0; i < dishCount; i++)
    {
        if (strcmp(dishes[i].id, dishId) == 0)
        {
            strcpy(newOrder.dish_id, dishId);
            sprintf(newOrder.id, "ORD%d", orderCount + 1); // Generate a unique order ID
            newOrder.status = 1;                           // Set status to placed
            orders[orderCount] = newOrder;                 // Add the new order to the orders array
            orderCount++;
            printf("Order placed successfully for '%s' with Order ID: %s\n", dishes[i].name, newOrder.id);
            dishFound = 1;
            break;
        }
    }

    if (!dishFound)
    {
        printf("Dish with ID %s not found or not available for ordering.\n", dishId);
    }
}

void searchDishes(struct Dish dishes[])
{
    char query[MAX_NAME_LENGTH];
    int found = 0;

    printf("Enter dish name or ID to search: ");
    scanf(" %[^\n]", query);

    printf("\n=== Search Results ===\n");
    for (int i = 0; i < dishCount; i++)
    {
        // Check if the dish name or ID matches the query
        if (strcmp(strlwr(dishes[i].name), strlwr(query)) == 0 || strcmp(strlwr(dishes[i].id), strlwr(query)) == 0)
        {
            printf("Dish ID: %s\n", dishes[i].id);
            printf("Name: %s\n", dishes[i].name);
            printf("Description: %s\n", dishes[i].description);
            printf("Price: %.2f\n", dishes[i].price);
            printf("Preparation Time: %d minutes\n", dishes[i].preparation_time);
            printf("-----------------------------\n");
            found = 1;
        }
    }

    if (!found)
    {
        printf("No dishes found matching '%s'.\n", query);
    }
}

void updateDish(struct Dish dishes[])
{
    char id[MAX_ID_LENGTH];
    printf("Enter dish ID to update: ");
    scanf("%s", id);

    int dishFound = 0;
    for (int i = 0; i < dishCount; i++)
    {
        if (strcmp(dishes[i].id, id) == 0)
        {
            dishFound = 1;

            // Display current dish details
            printf("Current details of Dish ID %s:\n", dishes[i].id);
            printf("Name: %s\n", dishes[i].name);
            printf("Description: %s\n", dishes[i].description);
            printf("Price: %.2f\n", dishes[i].price);
            printf("Preparation Time: %d minutes\n", dishes[i].preparation_time);

            // Prompt for new details
            printf("Enter new name ('keep' to keep current): ");
            char newName[MAX_NAME_LENGTH];
            scanf(" %[^\n]", newName);
            if (strcmp(strlwr(newName), strlwr("keep")) != 0)
            {
                strcpy(dishes[i].name, newName);
            }

            printf("Enter new description ('keep' to keep current): ");
            char newDescription[MAX_DESC_LENGTH];
            scanf(" %[^\n]", newDescription);
            if (strcmp(strlwr(newDescription), strlwr("keep")) != 0)
            {
                strcpy(dishes[i].description, newDescription);
            }

            printf("Enter new price (enter -1 to keep current): ");
            float newPrice;
            scanf("%f", &newPrice);
            if (newPrice >= 0)
            {
                dishes[i].price = newPrice;
            }

            printf("Enter new preparation time (enter -1 to keep current): ");
            int newPreparationTime;
            scanf("%d", &newPreparationTime);
            if (newPreparationTime >= 0)
            {
                dishes[i].preparation_time = newPreparationTime;
            }

            printf("Dish ID %s has been updated successfully!\n", dishes[i].id);
            break;
        }
    }

    if (!dishFound)
    {
        printf("Dish with ID %s not found.\n", id);
    }
}

void viewAllDishes(struct Dish dishes[])
{
    if (dishCount == 0)
    {
        printf("No dishes available.\n");
        return;
    }

    printf("\n=== List of All Dishes ===\n");
    printf("%-10s %-30s %-50s %-10s %-20s\n", "ID", "Name", "Description", "Price", "Preparation Time (min)");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < dishCount; i++)
    {
        printf("%-10s %-30s %-50s %-10.2f %-20d\n",
               dishes[i].id,
               dishes[i].name,
               dishes[i].description,
               dishes[i].price,
               dishes[i].preparation_time);
    }
}

void viewAllOrders(struct Order orders[])
{
    if (orderCount == 0)
    {
        printf("No orders available.\n");
        return;
    }

    printf("\n=== List of All Orders ===\n");
    printf("%-10s %-20s %-30s %-15s %-10s %-10s\n", "Order ID", "Customer Name", "Address", "Contact Number", "Dish ID", "Status");
    printf("---------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < orderCount; i++)
    {
        printf("%-10s %-20s %-30s %-15s %-10s %-10s\n",
               orders[i].id,
               orders[i].customer_name,
               orders[i].address,
               orders[i].contact_number,
               orders[i].dish_id,
               orders[i].status == 1 ? "Placed" : "Canceled");
    }
}

void viewSalesReport(struct Order orders[], struct Dish dishes[])
{
    if (orderCount == 0)
    {
        printf("No orders available to generate a sales report.\n");
        return;
    }

    float totalSales = 0.0;
    int totalOrders = 0;

    printf("\n=== Sales Report ===\n");
    printf("%-10s %-20s %-10s %-10s\n", "Dish ID", "Dish Name", "Quantity", "Total Price");
    printf("---------------------------------------------------------------\n");

    // A temporary array to count the number of orders for each dish
    int dishSales[MAX_DISHES] = {0};             // To keep track of quantities sold for each dish
    char dishNames[MAX_DISHES][MAX_NAME_LENGTH]; // To store names of dishes

    for (int i = 0; i < orderCount; i++)
    {
        if (orders[i].status == 1)
        { // Count only placed orders
            for (int j = 0; j < dishCount; j++)
            {
                if (strcmp(orders[i].dish_id, dishes[j].id) == 0)
                {
                    dishSales[j]++;
                    totalSales += dishes[j].price; // Add the price of the dish to total sales
                    break;                         // Found the dish, no need to check others
                }
            }
            totalOrders++;
        }
    }

    // Print report for each dish that has been ordered
    for (int i = 0; i < dishCount; i++)
    {
        if (dishSales[i] > 0)
        {                                                     // If the dish was sold at least once
            float dishTotal = dishSales[i] * dishes[i].price; // Calculate total for this dish
            printf("%-10s %-20s %-10d $%.2f\n",
                   dishes[i].id,
                   dishes[i].name,
                   dishSales[i],
                   dishTotal);
        }
    }

    printf("---------------------------------------------------------------\n");
    printf("Total Orders Placed: %d\n", totalOrders);
    printf("Total Sales: $%.2f\n", totalSales);
}
