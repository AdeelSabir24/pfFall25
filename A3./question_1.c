#include <stdio.h>

double calculateRepayment(double loan, double interestRate, int years,
                          double installment, double extraPayment) {
  if (years == 0 || loan <= 0) {
    return 0;
  }

  loan = loan + (loan * interestRate) - installment - extraPayment;

  if (loan < 0)
    loan = 0;

  printf("Year %d: Remaining loan = %.2f\n", years, loan);

  return installment + extraPayment +
         calculateRepayment(loan, interestRate, years - 1, installment,
                            extraPayment);
}

int main() {
  double loan = 100000;
  double interestRate = 0.05;
  int years = 3;
  double installment = loan / years;
  double extraPayment = 0;

  printf("Loan Repayment Schedule (Using Recursion):\n");
  printf("-----------------------------------------\n");

  double totalPaid =
      calculateRepayment(loan, interestRate, years, installment, extraPayment);

  printf("\nTotal Amount Paid Over %d Years = %.2f\n", years, totalPaid);

  return 0;
}
