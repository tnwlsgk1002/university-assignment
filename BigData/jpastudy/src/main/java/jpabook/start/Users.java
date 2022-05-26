package jpabook.start;

import com.sun.istack.NotNull;
import lombok.Getter;
import lombok.Setter;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.List;

@Getter
@Setter
@Entity
@Table(name="USERS")
public class Users extends BaseEntity{
    @Id
    @GeneratedValue
    @Column(name="USER_ID")
    private long id;

    @NotNull
    @Column(name="NAME")
    private String name;

    @NotNull
    @Column(name="AGE")
    private int age;

    @Embedded
    @Column(name="ADDRESS")
    private Address homeAddress;

    @OneToMany(mappedBy = "user", cascade = CascadeType.ALL)
    private List<Tickets> tickets = new ArrayList<>();

    public void printInfo() {
        System.out.println("사용자의 이름/나이/주소 : "+this.name+"/"+this.age+"/"
                +this.homeAddress.getCity() + "/"+ this.homeAddress.getStreet() + "/" + this.homeAddress.getZipCode());
    }
}
