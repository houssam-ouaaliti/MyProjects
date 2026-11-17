package blazing.jeux.entity;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class PlayerTest {

    @Test
    void setUsername_retourneCorrectement() {
        Player player = new Player();
        player.setUsername("alice");
        assertEquals("alice", player.getUsername());
    }

    @Test
    void setPasswordHash_retourneCorrectement() {
        Player player = new Player();
        player.setPasswordHash("secret123");
        assertEquals("secret123", player.getPasswordHash());
    }

    @Test
    void setId_retourneCorrectement() {
        Player player = new Player();
        player.setId(42L);
        assertEquals(42L, player.getId());
    }

    @Test
    void nouveauPlayer_champsNullParDefaut() {
        Player player = new Player();
        assertNull(player.getId());
        assertNull(player.getUsername());
        assertNull(player.getPasswordHash());
    }

    @Test
    void deuxPlayers_memesUsername_sontDifferents() {
        Player p1 = new Player();
        Player p2 = new Player();
        p1.setUsername("alice");
        p2.setUsername("alice");
        p1.setId(1L);
        p2.setId(2L);
        assertNotEquals(p1.getId(), p2.getId());
        assertEquals(p1.getUsername(), p2.getUsername());
    }
}