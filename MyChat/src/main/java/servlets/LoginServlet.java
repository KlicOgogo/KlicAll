package servlets;

import classes.User;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Formatter;

@WebServlet(value = "/login")

public class LoginServlet extends HttpServlet  {
    private User andrejka = new User();
    private User someone = new User();

    public LoginServlet() throws UnsupportedEncodingException, NoSuchAlgorithmException {
        super();
        andrejka = new User("andrejka", encryptPassword("password"));
        someone = new User("someone", encryptPassword("qwerty"));
    }
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        try {
            if (logOK(username, password)) {
                response.sendRedirect("/index.html");
            } else {
                response.sendRedirect("/notsuccess.html");
            }
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }
    private boolean logOK(String username, String password) throws UnsupportedEncodingException, NoSuchAlgorithmException {
        return username.equals(andrejka.getName()) && encryptPassword(password).equals(andrejka.getPassword()) || username.equals(someone.getName()) && encryptPassword(password).equals(someone.getPassword());
    }
    private String encryptPassword(String password) throws NoSuchAlgorithmException, UnsupportedEncodingException {
        String sha1;
        MessageDigest crypt = MessageDigest.getInstance("SHA-1");
        crypt.reset();
        crypt.update(password.getBytes("UTF-8"));
        Formatter formatter = new Formatter();
        for (byte b : crypt.digest()) {
            formatter.format("%02x", b);
        }
        sha1 = formatter.toString();
        formatter.close();
        return sha1;
    }
}
