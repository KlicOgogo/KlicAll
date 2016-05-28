package classes;

public class User {
    private String name;
    private String password;

    public User() {
        name = "";
        password = "";
    }
    public User(String name1, String password1) {
        name = name1;
        password = password1;
    }
    public String getName() {
        return name;
    }
    public String getPassword() {
        return password;
    }
}
