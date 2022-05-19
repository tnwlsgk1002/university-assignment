package jpabook.start;

import lombok.Getter;
import lombok.Setter;

import javax.persistence.*;

@Getter
@Setter
@Entity
@Inheritance(strategy = InheritanceType.JOINED)
@DiscriminatorColumn(name="DTYPE")
@Table(name="WORKERS")
public abstract class Workers {
    @Id
    @GeneratedValue
    @Column(name="WORKER_ID")
    private long id;

    @Column(name="NAME")
    private String name;

    @Column(name="AGE")
    private int age;
}