class Player:
    def __init__(self, x, y, width):
        self.x = 0
        self.y = 0
        self.width = width
        self.velocity = 2

    def set_position(self, x, y):
        self.x = x
        self.y = y
    
    def move(self, vel_x, vel_y):
        # Velocity based movement
        self.x = self.x + vel_x
        self.y = self.y + vel_y

        if self.x + self.width < 0: 
            self.x = 240
        elif self.x > 240:
            self.x = -self.width

        if self.y + self.width < 0: 
            self.y = 240
        elif self.y > 240:
            self.y = -self.width


player = Player(0,0, 40);

