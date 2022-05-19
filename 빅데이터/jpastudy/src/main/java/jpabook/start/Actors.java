package jpabook.start;

import lombok.Getter;
import lombok.Setter;

import javax.persistence.*;

@Getter
@Setter
@Entity
@DiscriminatorValue("A")
public class Actors extends Workers {
    @Column(name = "HEIGHT")
    private int height;

    @Column(name = "INSTA_ID")
    private String instaId;
}