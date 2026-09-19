# # ------- Problem 1 -----
# name = "100"
# try:
#     num = int(name)
#     print(f"Number: ", num)
# except ValueError as e:
#     print("Error Occured: ", e)


# # ------ Problem 2 -------
# name = "Python"
# try:
#     num = int(name)
#     print(f"Number: ", num)
# except ValueError as e:
#     print("Error Occured: ", e)
#     print(f"Cannot convert string to number")


# # -------- Problem 3 ----------


# try:
#     num = int(input("Enter a num: "))
#     a = 100 / num 

# except ZeroDivisionError as e:
#     print(f"Division by zero is invalid")


# # --------- Problem 4 -----------

# try:
#     num = int(input("Enter a num: "))
#     a = 100 / num 

# except ZeroDivisionError as e:
#     print(f"Division by zero is invalid")

# except ValueError as e :
#     print(f"Error Occured: ", e)


# # -------- Problem 5 ---------------



# try:
#     num = int(input("Enter a num: "))
#     a = 100 / num 

# except ZeroDivisionError as e:
#     print(f"Division by zero is invalid")

# finally :
#     print("Thankyou for using My App")





# # ------------------- Problem 1 ---------------

# class InvalidMarksError(Exception):
#     pass

# try:
#     marks = int(input("Enter your marks: "))

#     if(marks < 0 or marks > 100) :
#         raise InvalidMarksError (
#             f"Marks cannot be less than 0 or above 100"
#         )

# except InvalidMarksError as e:
#     print(f"Marks cannot be less than 0 or above 100")



# # ------------- Problem 2 ---------------
# class InvalidPasswordError(Exception):
#     pass

# try:
#     password = input("Enter your marks: ")

#     if(len(password) < 8) :
#         raise InvalidPasswordError (
#             f"Password cannot be less than 8 characters"
#         )

# except InvalidPasswordError as e:
#     print(f"Password cannot be less than 8 characters")


