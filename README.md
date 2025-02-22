# A-random-C-Win32-GUI-cart-manager-just-because

A simple Win32 GUI application written in C/C++ that loads a product list from a text file, imports these products into the GUI, allows the user to add products to a shopping cart, updates the total price, and prints a receipt to a text file.

## Features

- **Load Products:** Reads product names and prices from a `products.txt` file.
- **Add to Cart:** Select a product from the loaded list and add it to the cart.  
- **Total Price:** Automatically updates the total price as items are added.
- **Print Receipt:** Outputs the current cart items and total price to a `receipt.txt` file.

## Requirements
- Visual Studio 2022 (or later)
- Windows 7 or later
- C++14 compliant compiler

## Setup Instructions
1. **Clone the Repository:**
  ```
  git clone https://github.com/Scavix/A-random-C-Win32-GUI-cart-manager-just-because.git
  ```
2. **Open the Project:**
   Double-click the `ARandomWarehouseManagerInC.sln` file to open the solution in Visual Studio.
   
3. **Ensure `products.txt` is Present:**
   The application reads the product list from `products.txt`. Ensure this file is in the same directory as the executable (or adjust the path accordingly in the source code).

## Usage

1. **Build the Project:**
   Use Visual Studio's build functionality to compile the application.
   
3. **Run the Application:**
   The GUI will display a list of products loaded from `products.txt`.  
   - Select a product and click **Add to Cart** to add it.  
   - The total price updates automatically.  
   - Click **Print Receipt** to output the order to a `receipt.txt` file.

## Contributing
Feel free to fork the repository and submit pull requests for improvements.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
